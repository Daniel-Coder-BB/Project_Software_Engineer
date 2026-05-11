#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <algorithm>
#include "../Classes/Meetingplanner/Meetingplanner.h"
#include "../Classes/Buildings/Buildings.h"
#include "../Classes/Campus/Campus.h"
#include "../Classes/Room/Room.h"
#include "../Classes/Meeting/Meeting.h"
#include "../Classes/Participation/Participation.h"

using namespace std;

// ==========================================
// HULPFUNCTIES (I/O & Utilities)
// ==========================================
bool FileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

bool FileIsEmpty(const std::string& name) {
    std::ifstream file(name, std::ios::ate | std::ios::binary);
    return file.tellg() == 0;
}

bool FileCompare(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1);
    std::ifstream f2(file2);

    if (f1.fail() || f2.fail()) return false;

    std::string content1((std::istreambuf_iterator<char>(f1)), std::istreambuf_iterator<char>());
    std::string content2((std::istreambuf_iterator<char>(f2)), std::istreambuf_iterator<char>());

    content1.erase(std::remove(content1.begin(), content1.end(), '\r'), content1.end());
    content2.erase(std::remove(content2.begin(), content2.end(), '\r'), content2.end());

    return content1 == content2;
}

// ==========================================
// I/O EDGE CASES & FOUTEN (Fysieke bestanden)
// ==========================================
TEST(FileIOTest, IOTests_FileCompare) {
    ofstream myfile;
    myfile.open("../testOutput/file1.txt"); myfile.close();
    myfile.open("../testOutput/file2.txt"); myfile.close();

    EXPECT_TRUE(FileCompare("../testOutput/file1.txt", "../testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("../testOutput/file1.txt", "../testOutput/nonexisting.txt"));
}

// ==========================================
// OUTPUT TESTS FIXTURE
// ==========================================
class MeetingPlannerOutputTest : public ::testing::Test {
protected:
    MeetingPlanner planner;

    void SetupHappyDay() {
        Campus c; c.set_name("Middelheim"); c.set_identifier("CMI"); planner.set_campuses(c);
        Buildings b; b.set_name("G-Blok"); b.set_identifier("G.1"); b.set_campus("CMI"); planner.set_buildings(b);
        Room r; r.set_name("Room1"); r.set_identifier("R1"); r.set_capacity(20); r.set_campus("CMI"); r.set_building("G.1"); planner.addRoom(r);

        Meeting m1; m1.set_identifier("M1"); m1.set_label("Sync"); m1.set_room("R1");
        m1.set_date("2026-05-15"); m1.set_hour(10); m1.set_online(false); m1.set_catering(true);
        planner.addMeeting(m1);

        Participation p1; p1.set_user("Alice"); p1.set_meeting("M1"); planner.addParticipation(p1);
        Participation p2; p2.set_user("Bob"); p2.set_meeting("M1"); planner.addParticipation(p2);
    }
};

// ==========================================
// 1. ALGEMENE CORRECTHEID (Happy Day)
// ==========================================
TEST_F(MeetingPlannerOutputTest, HappyDay_SimpleOutput) {
    SetupHappyDay();
    planner.simpleOutput();
    EXPECT_TRUE(FileCompare("../output.txt", "../testOutput/expected_happy_day_output.txt"));
}

TEST_F(MeetingPlannerOutputTest, HappyDay_Graphviz) {
    SetupHappyDay();
    planner.exportGraphviz();
    EXPECT_TRUE(FileCompare("../structure.dot", "../testOutput/expected_happy_day_structure.dot"));
}

// ==========================================
// 2. BESTAAN: COMBINATORISCHE TESTS (Lege/Volle elementen)
// ==========================================
// Combinatie 1: Alles leeg -> Preconditie faalt
TEST_F(MeetingPlannerOutputTest, Combinatie_LegeRooms_LegeMeetings) {
    EXPECT_DEATH(planner.simpleOutput(), "attributes of meetingplanner are not Empty");
}

// Combinatie 2: Rooms vol, Meetings leeg (Kardinaliteit test)
TEST_F(MeetingPlannerOutputTest, Combinatie_VolleRooms_LegeMeetings) {
    Room r; r.set_name("Room1"); r.set_identifier("R1"); r.set_capacity(20); r.set_campus("Middelheim"); r.set_building("M");
    planner.addRoom(r);
    planner.simpleOutput();
    EXPECT_TRUE(FileCompare("../output.txt", "../testOutput/expected_rooms_only.txt"));
}

// Combinatie 3: Rooms leeg, Meetings vol (Valid, maar rare output)
TEST_F(MeetingPlannerOutputTest, Combinatie_LegeRooms_VolleMeetings) {
    Meeting m;
    m.set_identifier("M1");
    m.set_online(true);
    m.set_date("2026-06-14");
    m.set_room("ONLINE"); // Stel expliciet een room-identifier in om crashes te voorkomen

    planner.addMeeting(m);
    planner.simpleOutput();
    EXPECT_TRUE(FileCompare("../output.txt", "../testOutput/expected_lege_rooms_volle_meetings.txt"));
}

// Graphviz Combinaties
TEST_F(MeetingPlannerOutputTest, Graphviz_Combinatie_AlleenRooms) {
    Room r; r.set_name("Room1"); r.set_identifier("R1");
    planner.addRoom(r); // Campuses, Buildings en Meetings zijn leeg
    planner.exportGraphviz();
    EXPECT_TRUE(FileCompare("../structure.dot", "../testOutput/expected_dot_only_rooms.dot"));
}

// ==========================================
// 3. ORDE: Heeft een andere volgorde effect?
// ==========================================
TEST_F(MeetingPlannerOutputTest, Orde_ToevoegenVerandertOutput) {
    // We voegen R2 eerst toe, daarna R1. Ze moeten in die volgorde in het bestand staan.
    Room r2; r2.set_identifier("R2"); r2.set_name("Room 2"); r2.set_campus("Mid"); r2.set_building("M"); planner.addRoom(r2);
    Room r1; r1.set_identifier("R1"); r1.set_name("Room 1"); r1.set_campus("Mid"); r1.set_building("M"); planner.addRoom(r1);

    planner.simpleOutput();
    EXPECT_TRUE(FileCompare("../output.txt", "../testOutput/expected_orde_omgekeerd.txt"));
}

// ==========================================
// 4. BEREIK & KARDINALITEIT (0 vs Maximum waarden)
// ==========================================
TEST_F(MeetingPlannerOutputTest, Bereik_NulParticipanten_Vs_Massaal) {
    Room r; r.set_identifier("R1"); r.set_name("Groot Lokaal"); r.set_capacity(50000); r.set_campus("Mid"); r.set_building("M");
    planner.addRoom(r);

    // Meeting met 0 participanten
    Meeting m_zero; m_zero.set_identifier("M_ZERO"); m_zero.set_room("R1"); m_zero.set_online(false); m_zero.set_date("2026-05-11");
    planner.addMeeting(m_zero);

    // Meeting met 1000 participanten
    Meeting m_many; m_many.set_identifier("M_MANY"); m_many.set_room("R1"); m_many.set_online(false); m_many.set_date("2026-05-11");
    planner.addMeeting(m_many);

    for(int i = 0; i < 1000; i++) {
        Participation p; p.set_meeting("M_MANY"); p.set_user("User_" + to_string(i));
        planner.addParticipation(p);
    }

    planner.simpleOutput();
    EXPECT_TRUE(FileCompare("../output.txt", "../testOutput/expected_bereik_participanten.txt"));
}

// ==========================================
// 5. FOUTEN & EXCEPTIONS (Precondities)
// ==========================================
TEST_F(MeetingPlannerOutputTest, Fouten_OnlineMeetingMetCatering_InOutput) {
    // Zet een illegale status op (online + catering)
    Room r; r.set_identifier("R1"); r.set_name("Kamer"); planner.addRoom(r);
    Meeting m; m.set_identifier("M_ILLEGAAL"); m.set_online(true); m.set_catering(true);
    planner.addMeeting(m);

    // simpleOutput iterereert over meetings. Wanneer hij bij catering aankomt, hoort hij te crashen.
    EXPECT_DEATH(planner.simpleOutput(), "Online meetings cannot have catering");
}

TEST_F(MeetingPlannerOutputTest, Fouten_GraphvizLegeKamers) {
    // exportGraphviz vereist minstens 1 kamer
    EXPECT_DEATH(planner.exportGraphviz(), "rooms must not be empty");
}