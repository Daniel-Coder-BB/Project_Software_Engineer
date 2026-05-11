#include <gtest/gtest.h>
#include "../tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "../Classes/Parser/Parser.h"
#include "../Classes/Meetingplanner/Meetingplanner.h"
#include "../Classes/Room/Room.h"
#include "../Classes/Meeting/Meeting.h"

using namespace std;

// ==========================================
// PARSER XML ELEMENT INPUT TESTS
// ==========================================
TEST(ParserInputTest, ParseElements_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<CAMPUS><NAME>Middelheim</NAME><IDENTIFIER>CMI</IDENTIFIER></CAMPUS>");
    Campus c = p.parse_campus_element(doc.FirstChildElement("CAMPUS"));
    EXPECT_EQ(c.get_name(), "Middelheim");

    doc.Parse("<ROOM><NAME>Aula</NAME><IDENTIFIER>A.01</IDENTIFIER><CAPACITY>150</CAPACITY></ROOM>");
    Room r = p.parse_room_element(doc.FirstChildElement("ROOM"));
    EXPECT_EQ(r.get_name(), "Aula");
    EXPECT_EQ(r.get_capacity(), 150);
}

TEST(ParserInputTest, ParseElements_MissingOrEmptyTags) {
    Parser p;
    TiXmlDocument doc;
    
    // Missende data
    doc.Parse("<ROOM><NAME>Aula</NAME><IDENTIFIER>A.01</IDENTIFIER></ROOM>");
    Room r = p.parse_room_element(doc.FirstChildElement("ROOM"));
    EXPECT_EQ(r.get_name(), "Fout");
    EXPECT_EQ(r.get_capacity(), 0);

    // Lege data
    doc.Parse("<MEETING><LABEL></LABEL><IDENTIFIER>ID</IDENTIFIER><ROOM>A1</ROOM><DATE>Today</DATE></MEETING>");
    Meeting m = p.parse_meeting_element(doc.FirstChildElement("MEETING"));
    EXPECT_EQ(m.get_label(), "fout");
}

TEST(ParserInputTest, ContractViolations) {
    Parser p;
    EXPECT_DEATH(p.parse_campus_element(nullptr), ".*");
    EXPECT_DEATH(p.parse_room_element(nullptr), "Preconditie gefaald: room_element mag niet NULL zijn");
}

// ==========================================
// FILE IMPORT SCENARIO TESTS (TicTacToe Style)
// ==========================================
class FileImportInputTest : public ::testing::Test {
protected:
    Parser p;
    MeetingPlanner planner;
};

TEST_F(FileImportInputTest, InputHappyDay) {
    // Zorg dat testInput/happy_day.xml bestaat in je test directory!
    p.set_filename("testInput/happy_day.xml");
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(0, p.file_error_check(doc));
    
    TiXmlElement* root = p.make_root(doc);
    ASSERT_NE(root, nullptr);
}

TEST_F(FileImportInputTest, InputXMLSyntaxErrors) {
    p.set_filename("testInput/corrupt.xml"); // Zorg dat dit bestand express corrupt is
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(1, p.file_error_check(doc));
}

TEST_F(FileImportInputTest, InputMissingFile) {
    p.set_filename("testInput/bestaat_niet.xml");
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(1, p.file_error_check(doc));
}

// ==========================================
// LOGICAL INPUT PROCESSING TESTS
// ==========================================
TEST(MeetingPlannerInputTest, ProcessMeetings_RenovationConflict) {
    MeetingPlanner planner;

    Renovations ren;
    ren.set_room("B.0.01");
    ren.set_start("09:00");
    ren.set_end("17:00");
    planner.set_renovations(ren);

    Meeting m;
    m.set_identifier("M3");
    m.set_room("B.0.01");
    m.set_online(false);
    m.set_catering(true);
    planner.addMeeting(m);

    planner.processMeetings();

    // De meeting moet genegeerd/geannuleerd worden wegens renovatie
    EXPECT_DOUBLE_EQ(planner.totalCateringCost, 0.0);
}

TEST(MeetingPlannerInputTest, ProcessMeetings_OccupiedRoom) {
    MeetingPlanner planner;
    planner.set_occupied_rooms("C.1.02");

    Meeting m;
    m.set_identifier("M_OCCUPIED_TEST");
    m.set_room("C.1.02");
    m.set_online(false);
    m.set_catering(true);
    planner.addMeeting(m);

    planner.processMeetings();

    // De meeting kan niet doorgaan in een bezette kamer
    EXPECT_DOUBLE_EQ(planner.totalCateringCost, 0.0);
}