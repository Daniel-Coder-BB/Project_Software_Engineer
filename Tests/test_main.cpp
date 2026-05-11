#include "../gtest-1.7.0/include/gtest/gtest.h"
#include <iostream>
#include "../tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "../Classes/Room/Room.h"
#include "../Classes/Meeting/Meeting.h"
#include <pstl/execution_defs.h>
#include "../Classes/Participation/Participation.h"
#include "../Classes/Meetingplanner/Meetingplanner.h"
#include "../Classes/Parser/Parser.h"
#include "../Classes/Buildings/Buildings.h"
#include "../Classes/Campus/Campus.h"
#include "../Classes/CateringProviders/Cateringproviders.h"
#include "Classes/Renovations/Renovations.h"
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(ParserTest, ParseCampus_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<CAMPUS><NAME>Middelheim</NAME><IDENTIFIER>CMI</IDENTIFIER></CAMPUS>");
    TiXmlElement* el = doc.FirstChildElement("CAMPUS");

    Campus c = p.parse_campus_element(el);

    EXPECT_EQ(c.get_name(), "Middelheim");
    EXPECT_EQ(c.get_identifier(), "CMI");
}

TEST(ParserTest, ParseBuilding_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<BUILDING><NAME>G-Gebouw</NAME><IDENTIFIER>G.1</IDENTIFIER><CAMPUS>CMI</CAMPUS></BUILDING>");
    TiXmlElement* el = doc.FirstChildElement("BUILDING");

    Buildings b = p.parse_building_element(el);

    EXPECT_EQ(b.get_name(), "G-Gebouw");
    EXPECT_EQ(b.get_campus(), "CMI");
}

TEST(ParserTest, ParseRenovation_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<RENOVATION><ROOM>G.1.01</ROOM><START>08:00</START><END>12:00</END></RENOVATION>");
    TiXmlElement* el = doc.FirstChildElement("RENOVATION");

    Renovations r = p.parse_renovation_element(el);

    EXPECT_EQ(r.get_room(), "G.1.01");
    EXPECT_EQ(r.get_start(), "08:00");
}

TEST(ParserTest, ParseCatering_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<CATERING><CAMPUS>CMI</CAMPUS><CO2>12.5</CO2></CATERING>");
    TiXmlElement* el = doc.FirstChildElement("CATERING");

    Cateringproviders c = p.parse_catering_element(el);

    EXPECT_EQ(c.get_campus(), "CMI");
    EXPECT_FLOAT_EQ(c.get_co2(), 12.5f);
}

TEST(ParserTest, ParseElement_NullPointers) {
    Parser p;
    EXPECT_DEATH(p.parse_campus_element(nullptr), ".*");
    EXPECT_DEATH(p.parse_building_element(nullptr), ".*");
    EXPECT_DEATH(p.parse_renovation_element(nullptr), ".*");
    EXPECT_DEATH(p.parse_catering_element(nullptr), ".*");
}

TEST(ParserTest, GetFilename_HappyDay) {
    Parser p;
    string naam = "mijnBestand.xml";
    p.set_filename(naam);

    EXPECT_EQ(p.get_filename(), naam);
}

TEST(ParserTest, GetFilename_Boundaries) {
    Parser p;
    p.set_filename("a");
    EXPECT_EQ(p.get_filename(), "a");

    p.set_filename("test file @ v2.txt");
    EXPECT_EQ(p.get_filename(), "test file @ v2.txt");
}

TEST(ParserTest, GetFilename_ContractViolation) {
    Parser p;
    EXPECT_DEATH(p.get_filename(), "Preconditie gefaald: filename mag niet leeg zijn");
}

TEST(ParserTest, SetFilename_HappyDay) {
    Parser p;
    string nieuweNaam = "config.xml";

    p.set_filename(nieuweNaam);

    EXPECT_EQ(p.get_filename(), nieuweNaam);
}

TEST(ParserTest, SetFilename_Boundaries) {
    Parser p;
    p.set_filename("z");
    EXPECT_EQ(p.get_filename(), "z");

    p.set_filename("   ");
    EXPECT_EQ(p.get_filename(), "   ");
}

TEST(ParserTest, SetFilename_ContractViolation) {
    Parser p;
    string legeNaam = "";
    EXPECT_DEATH(p.set_filename(legeNaam), "Preconditie gefaald: nieuwe filename mag niet leeg zijn");
}

TEST(ParserTest, SetFilename_Overwrite) {
    Parser p;
    p.set_filename("oud.xml");
    p.set_filename("nieuw.xml");

    EXPECT_EQ(p.get_filename(), "nieuw.xml");
}

TEST(ParserTest, XmlToDoc_HappyDay) {
    Parser p;
    p.set_filename("../Tests/test_XML_file/happy_day.xml");

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();

    EXPECT_FALSE(doc.Error());
}

TEST(ParserTest, XmlToDoc_EmptyFile) {
    Parser p;
    p.set_filename("../Tests/test_XML_file/rootless.xml");

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    EXPECT_TRUE(doc.Error());
}

TEST(ParserTest, XmlToDoc_InvalidXML) {
    Parser p;
    p.set_filename("not_a_xml.txt");

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    EXPECT_TRUE(doc.Error());
}

TEST(ParserTest, XmlToDoc_ContractViolation) {
    Parser p;
    EXPECT_DEATH(p.Xml_to_TiXmlDocument(), "Preconditie gefaald: filename mag niet leeg zijn");
}

TEST(ParserTest, XmlToDoc_MissingFile) {
    Parser p;
    p.set_filename("bestaat_niet.xml");

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    EXPECT_TRUE(doc.Error());
}

TEST(ParserTest, FileErrorCheck_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("../Tests/test_XML_file/happy_day.xml");

    int result = p.file_error_check(doc);

    EXPECT_EQ(result, 0);
    EXPECT_FALSE(doc.Error());
}

TEST(ParserTest, FileErrorCheck_EmptyFile) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("../Tests/test_XML_file/rootless.xml");

    int result = p.file_error_check(doc);

    EXPECT_EQ(result, 1);
}

TEST(ParserTest, FileErrorCheck_CorruptXML) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("../Tests/test_XML_file/corrupt.xml");

    int result = p.file_error_check(doc);

    EXPECT_EQ(result, 1);
}

TEST(ParserTest, FileErrorCheck_MissingFile) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("non_existent_file_999.xml");

    int result = p.file_error_check(doc);

    EXPECT_EQ(result, 1);
}

TEST(ParserTest, FileErrorCheck_ContractViolation) {
    Parser p;
    TiXmlDocument doc;
    EXPECT_DEATH(p.file_error_check(doc), "Preconditie gefaald: filename mag niet leeg zijn");
}

TEST(ParserTest, IfRootExists_HappyDay) {
    Parser p;
    TiXmlElement root("MyRoot");

    int result = p.if_root_exists(&root);

    EXPECT_EQ(result, 0);
}

TEST(ParserTest, IfRootExists_NullPointer) {
    Parser p;
    TiXmlElement* legeRoot = NULL;

    int result = p.if_root_exists(legeRoot);

    EXPECT_EQ(result, 1);
}

TEST(ParserTest, MakeRoot_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<system><subelement/></system>");

    TiXmlElement* root = p.make_root(doc);

    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Value(), "system");
}

TEST(ParserTest, MakeRoot_EmptyDocument) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("");

    TiXmlElement* root = p.make_root(doc);

    EXPECT_EQ(root, nullptr);
}

TEST(ParserTest, MakeRoot_AfterFileError) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<open-tag-zonder-sluiting");

    ASSERT_TRUE(doc.Error());

    TiXmlElement* root = p.make_root(doc);
    EXPECT_EQ(root, nullptr);
}

TEST(ParserTest, MakeRoot_CorrectElement) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<eerste>...</eerste><tweede>...</tweede>");

    TiXmlElement* root = p.make_root(doc);

    EXPECT_STREQ(root->Value(), "eerste");
}

TEST(ParserTest, ParseRoom_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<ROOM><NAME>Aula</NAME><IDENTIFIER>A.01</IDENTIFIER><CAPACITY>150</CAPACITY></ROOM>");
    TiXmlElement* room_el = doc.FirstChildElement("ROOM");

    Room r = p.parse_room_element(room_el);

    EXPECT_EQ(r.get_name(), "Aula");
    EXPECT_EQ(r.get_identifier(), "A.01");
    EXPECT_EQ(r.get_capacity(), 150);
}

TEST(ParserTest, ParseRoom_MissingTags) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<ROOM><NAME>Aula</NAME><IDENTIFIER>A.01</IDENTIFIER></ROOM>");
    TiXmlElement* room_el = doc.FirstChildElement("ROOM");

    Room r = p.parse_room_element(room_el);

    EXPECT_EQ(r.get_name(), "Fout");
    EXPECT_EQ(r.get_capacity(), 0);
}

TEST(ParserTest, ParseRoom_EmptyTags) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<ROOM><NAME></NAME><IDENTIFIER>A.01</IDENTIFIER><CAPACITY>100</CAPACITY></ROOM>");
    TiXmlElement* room_el = doc.FirstChildElement("ROOM");

    Room r = p.parse_room_element(room_el);
    EXPECT_EQ(r.get_name(), "Fout");
}

TEST(ParserTest, ParseRoom_InvalidCapacity) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<ROOM><NAME>Lab</NAME><IDENTIFIER>L.01</IDENTIFIER><CAPACITY>abc</CAPACITY></ROOM>");
    TiXmlElement* room_el = doc.FirstChildElement("ROOM");

    Room r = p.parse_room_element(room_el);
    EXPECT_EQ(r.get_capacity(), 0);
    EXPECT_EQ(r.get_name(), "Fout");
}

TEST(ParserTest, ParseRoom_ContractViolation) {
    Parser p;
    EXPECT_DEATH(p.parse_room_element(nullptr), "Preconditie gefaald: room_element mag niet NULL zijn");
}

TEST(ParserTest, ParseMeeting_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<MEETING><LABEL>Projectoverleg</LABEL><IDENTIFIER>M001</IDENTIFIER>"
              "<ROOM>A.01</ROOM><DATE>2024-05-12</DATE></MEETING>");
    TiXmlElement* meet_el = doc.FirstChildElement("MEETING");

    Meeting m = p.parse_meeting_element(meet_el);

    EXPECT_EQ(m.get_label(), "Projectoverleg");
    EXPECT_EQ(m.get_identifier(), "M001");
    EXPECT_EQ(m.get_room(), "A.01");
    EXPECT_EQ(m.get_date(), "2024-05-12");
}

TEST(ParserTest, ParseMeeting_MissingTag) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<MEETING><LABEL>Test</LABEL><IDENTIFIER>ID</IDENTIFIER><ROOM>A1</ROOM></MEETING>");
    TiXmlElement* meet_el = doc.FirstChildElement("MEETING");

    Meeting m = p.parse_meeting_element(meet_el);

    EXPECT_EQ(m.get_label(), "fout");
    EXPECT_EQ(m.get_date(), "fout");
}

TEST(ParserTest, ParseMeeting_EmptyTagHandling) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<MEETING><LABEL></LABEL><IDENTIFIER>ID</IDENTIFIER><ROOM>A1</ROOM><DATE>Today</DATE></MEETING>");
    TiXmlElement* meet_el = doc.FirstChildElement("MEETING");

    Meeting m = p.parse_meeting_element(meet_el);

    EXPECT_EQ(m.get_label(), "fout");
    EXPECT_EQ(m.get_identifier(), "fout");
}

TEST(ParserTest, ParseMeeting_ContractViolation) {
    Parser p;
    EXPECT_DEATH(p.parse_meeting_element(nullptr), "Preconditie gefaald: meeting_element mag niet NULL zijn");
}

TEST(ParserTest, ParseParticipation_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<PARTICIPATION><USER>JanDeMan</USER><MEETING>M001</MEETING></PARTICIPATION>");
    TiXmlElement* el = doc.FirstChildElement("PARTICIPATION");

    Participation part = p.parse_participation_element(el);

    EXPECT_EQ(part.get_user(), "JanDeMan");
    EXPECT_EQ(part.get_meeting(), "M001");
}

TEST(ParserTest, ParseParticipation_EmptyTags) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<PARTICIPATION><USER></USER><MEETING>M001</MEETING></PARTICIPATION>");
    TiXmlElement* el = doc.FirstChildElement("PARTICIPATION");

    Participation part = p.parse_participation_element(el);

    EXPECT_EQ(part.get_user(), "fout");
    EXPECT_EQ(part.get_meeting(), "fout");
}

TEST(ParserTest, ParseParticipation_MissingTags) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<PARTICIPATION><USER>Jan</USER></PARTICIPATION>");
    TiXmlElement* el = doc.FirstChildElement("PARTICIPATION");

    Participation part = p.parse_participation_element(el);

    EXPECT_EQ(part.get_meeting(), "fout");
    EXPECT_EQ(part.get_user(), "fout");
}

TEST(ParserTest, ParseParticipation_NullPointer) {
    Parser p;
    EXPECT_DEATH(p.parse_participation_element(NULL), "Preconditie gefaald: participation_element mag niet NULL zijn");
}

TEST(ParserTest, RunThroughElement_HappyDay) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    doc.Parse("<ROOT><ROOM><NAME>A1</NAME><IDENTIFIER>ID1</IDENTIFIER><CAPACITY>10</CAPACITY></ROOM>"
              "<ROOM><NAME>B2</NAME><IDENTIFIER>ID2</IDENTIFIER><CAPACITY>20</CAPACITY></ROOM></ROOT>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    p.run_trough_Element("ROOM", root, planner);

    EXPECT_EQ(planner.getRooms().size(), 2ULL);
}

TEST(ParserTest, RunThroughElement_SkipErrors) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    doc.Parse("<ROOT><ROOM><NAME>Goed</NAME><IDENTIFIER>I1</IDENTIFIER><CAPACITY>10</CAPACITY></ROOM>"
              "<ROOM><NAME></NAME><IDENTIFIER>I2</IDENTIFIER><CAPACITY>10</CAPACITY></ROOM></ROOT>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    p.run_trough_Element("ROOM", root, planner);

    EXPECT_EQ(planner.getRooms().size(), 1ULL);
}

TEST(ParserTest, RunThroughElement_InvalidTagName) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    doc.Parse("<ROOT/>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    EXPECT_DEATH(p.run_trough_Element("AUTO", root, planner), "Element moet .* zijn");
}

TEST(ParserTest, RunThroughElement_NullRoot) {
    Parser p;
    MeetingPlanner planner;
    EXPECT_DEATH(p.run_trough_Element("ROOM", NULL, planner), "root moet bestaan");
}

TEST(ParserTest, RunThroughElement_MeetingKardinaliteit) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    doc.Parse("<ROOT><MEETING><LABEL>A</LABEL><IDENTIFIER>1</IDENTIFIER><ROOM>R1</ROOM><DATE>D1</DATE></MEETING></ROOT>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    p.run_trough_Element("MEETING", root, planner);
    EXPECT_EQ(planner.getMeetings().size(), 1ULL);
}

class MeetingPlannerDomainTest : public ::testing::Test {
protected:
    MeetingPlanner planner;
};

TEST_F(MeetingPlannerDomainTest, CalculateCO2_PhysicalMeeting) {
    Room r;
    r.set_name("Lokaal 1.01");
    r.set_identifier("M1_Room");
    r.set_capacity(50);
    planner.addRoom(r);

    Meeting m;
    m.set_identifier("M1");
    m.set_room("M1_Room");
    m.set_online(false);
    planner.addMeeting(m);

    Participation p;
    p.set_user("Ibrahim");
    p.set_meeting("M1");
    planner.addParticipation(p);

    EXPECT_DOUBLE_EQ(planner.calculateCO2(m), 120.0);
}

TEST_F(MeetingPlannerDomainTest, MeetingCapacity_Check) {
    Room r;
    r.set_name("Lokaal 1");
    r.set_identifier("L.1.01");
    r.set_capacity(50);
    planner.addRoom(r);

    Meeting m;
    m.set_room("L.1.01");

    EXPECT_EQ(planner.meeting_capacity(m), 50);
}

TEST_F(MeetingPlannerDomainTest, CO2_OnlineCatering_Violation) {
    Meeting m;
    m.set_identifier("M2");
    m.set_online(true);
    m.set_catering(true);

    EXPECT_DEATH(planner.calculateCO2(m), "Online meetings cannot have catering");
}

TEST_F(MeetingPlannerDomainTest, AddRoom_EmptyName_Violation) {
    Room r;
    EXPECT_DEATH(planner.addRoom(r), "name is not empty");
}

TEST(MeetingPlannerInputTest, ProcessMeetings_RenovationConflict) {
    MeetingPlanner planner;

    Renovations ren;
    ren.set_room("B.0.01");
    ren.set_start("09:00");
    ren.set_end("17:00");
    planner.set_renovations(ren);

    Meeting m;
    m.set_identifier("M3");
    m.set_label("Project Meeting");
    m.set_room("B.0.01");
    m.set_online(false);
    m.set_catering(true);
    planner.addMeeting(m);

    planner.processMeetings();

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

    EXPECT_DOUBLE_EQ(planner.totalCateringCost, 0.0);
}

TEST(MeetingPlannerOutputTest, SimpleOutput_FileCreation) {
    MeetingPlanner planner;

    Room r;
    r.set_name("G-Gebouw");
    r.set_identifier("G1");
    r.set_capacity(10);

    planner.addRoom(r);

    planner.simpleOutput();

    std::ifstream file("../output.txt");
    EXPECT_TRUE(file.good());
    file.close();
}

TEST(MeetingPlannerOutputTest, Graphviz_CheckStructure) {
    MeetingPlanner planner;

    Buildings b;
    b.set_name("G-Blok");
    b.set_identifier("G.1");
    b.set_campus("Middelheim");
    planner.set_buildings(b);

    Room r;
    r.set_identifier("R1");
    r.set_name("Room1");
    r.set_capacity(20);
    planner.addRoom(r);

    planner.exportGraphviz();

    std::ifstream file("../structure.dot");
    ASSERT_TRUE(file.is_open()) << "structure.dot kon niet worden geopend.";

    std::string line;
    bool foundLink = false;
    while (std::getline(file, line)) {
        if (line.find("-> \"R1\"") != std::string::npos) foundLink = true;
    }

    file.close();
    EXPECT_TRUE(foundLink) << "De link tussen gebouw en kamer werd niet gevonden in het DOT-bestand.";
}

class BuildingsDomainTest : public ::testing::Test {
protected:
    Buildings testBuilding;
};

TEST_F(BuildingsDomainTest, HappyDaySettersGetters) {
    testBuilding.set_name("G-gebouw");
    testBuilding.set_identifier("G.1.01");
    testBuilding.set_campus("Middelheim");

    EXPECT_EQ(testBuilding.get_name(), "G-gebouw");
    EXPECT_EQ(testBuilding.get_identifier(), "G.1.01");
    EXPECT_EQ(testBuilding.get_campus(), "Middelheim");
}

TEST_F(BuildingsDomainTest, BoundaryEmptyStringsViolation) {
    EXPECT_DEATH(testBuilding.set_name(""), "Precondition failure: name cannot be empty");
    EXPECT_DEATH(testBuilding.set_identifier(""), "Precondition failure: identifier cannot be empty");
}

TEST_F(BuildingsDomainTest, OverwriteValues) {
    testBuilding.set_name("Oud");
    testBuilding.set_name("Nieuw");
    EXPECT_EQ(testBuilding.get_name(), "Nieuw");
}

std::string formatBuilding(const Buildings& b) {
    return b.get_name() + " (" + b.get_identifier() + ")";
}

TEST(BuildingsOutputTest, OutputHappyDay) {
    Buildings b;
    b.set_name("Gebouw B");
    b.set_identifier("B.123");

    std::string expected = "Gebouw B (B.123)";
    EXPECT_EQ(formatBuilding(b), expected);
}

TEST(BuildingsInputTest, InputLegalData) {
    std::string inputName = "C-gebouw";
    std::string inputID = "C.0.01";
    std::string inputCampus = "Groenenborger";

    Buildings b;
    b.set_name(inputName);
    b.set_identifier(inputID);
    b.set_campus(inputCampus);

    EXPECT_EQ(b.get_campus(), "Groenenborger");
}

TEST(BuildingsInputTest, InputSpecialCharacters) {
    Buildings b;
    b.set_name("Bâtiment-X 2.0");
    EXPECT_EQ(b.get_name(), "Bâtiment-X 2.0");
}

TEST_F(BuildingsDomainTest, TestExtremeStringLength) {
    std::string longName(5000, 'A');
    testBuilding.set_name(longName);
    EXPECT_EQ(testBuilding.get_name().length(), 5000u);
}

class CampusDomainTest : public ::testing::Test {
protected:
    Campus testCampus;
};

TEST_F(CampusDomainTest, HappyDaySettersGetters) {
    testCampus.set_name("Middelheim");
    testCampus.set_identifier("CMI");

    EXPECT_EQ(testCampus.get_name(), "Middelheim");
    EXPECT_EQ(testCampus.get_identifier(), "CMI");
}

TEST_F(CampusDomainTest, BoundaryEmptyStringsViolation) {
    EXPECT_DEATH(testCampus.set_name(""), "Precondition failure: name cannot be empty");
}

TEST_F(CampusDomainTest, TestOrderOfOperations) {
    testCampus.set_identifier("GGB");
    testCampus.set_name("Groenenborger");

    EXPECT_EQ(testCampus.get_name(), "Groenenborger");
    EXPECT_EQ(testCampus.get_identifier(), "GGB");
}

TEST_F(CampusDomainTest, TestLongStringRange) {
    std::string longName(1000, 'A');
    testCampus.set_name(longName);
    EXPECT_EQ(testCampus.get_name().length(), 1000u);
}

std::string displayCampus(const Campus& c) {
    return "[" + c.get_identifier() + "] " + c.get_name();
}

TEST(CampusOutputTest, OutputFormatCorrectness) {
    Campus c;
    c.set_name("Drie Eiken");
    c.set_identifier("CDE");

    std::string expected = "[CDE] Drie Eiken";
    EXPECT_EQ(displayCampus(c), expected);
}

TEST(CampusInputTest, InputMissingDataViolation) {
    Campus c;
    std::string inputID = "";

    EXPECT_DEATH(c.set_identifier(inputID), "Precondition failure: identifier cannot be empty");
}

TEST(CampusInputTest, InputSpecialCharacters) {
    Campus c;
    c.set_name("Campus @ Stadscampus #1");
    EXPECT_EQ(c.get_name(), "Campus @ Stadscampus #1");
}

class CateringprovidersDomainTest : public ::testing::Test {
protected:
    Cateringproviders testProvider;
};

TEST_F(CateringprovidersDomainTest, HappyDaySettersGetters) {
    testProvider.set_campus("Campus Middelheim");
    testProvider.set_co2(15.5f);

    EXPECT_EQ(testProvider.get_campus(), "Campus Middelheim");
    EXPECT_FLOAT_EQ(testProvider.get_co2(), 15.5f);
}

TEST_F(CateringprovidersDomainTest, TestCO2PreconditionViolation) {
    EXPECT_DEATH(testProvider.set_co2(0.0f), "Precondition failure: Value must be greater then zero");
    EXPECT_DEATH(testProvider.set_co2(-1.0f), "Precondition failure: Value must be greater then zero");
}

TEST_F(CateringprovidersDomainTest, BoundaryEmptyCampus) {
    EXPECT_DEATH(testProvider.set_campus(""), "Precondition failure: campus cannot be empty");
}

string formatCateringReport(const Cateringproviders& p) {
    return "Campus: " + p.get_campus() + " (CO2: " + to_string(p.get_co2()) + ")";
}

TEST(CateringprovidersOutputTest, OutputFormat) {
    Cateringproviders p;
    p.set_campus("Groenenborger");
    p.set_co2(20.0f);

    string report = formatCateringReport(p);
    EXPECT_NE(report.find("Groenenborger"), string::npos);
    EXPECT_NE(report.find("20.0"), string::npos);
}

TEST(CateringprovidersInputTest, InputLargeNumericalValue) {
    Cateringproviders p;
    float maxCO2 = 1000000.0f;
    p.set_co2(maxCO2);
    EXPECT_FLOAT_EQ(p.get_co2(), 1000000.0f);
}

class RenovationsDomainTest : public ::testing::Test {
protected:
    Renovations testRenovation;
};

TEST_F(RenovationsDomainTest, HappyDaySettersGetters) {
    testRenovation.set_room("L.1.01");
    testRenovation.set_start("08:00");
    testRenovation.set_end("17:00");

    EXPECT_EQ(testRenovation.get_room(), "L.1.01");
    EXPECT_EQ(testRenovation.get_start(), "08:00");
    EXPECT_EQ(testRenovation.get_end(), "17:00");
}

TEST_F(RenovationsDomainTest, EmptyRoomViolation) {
    EXPECT_DEATH(testRenovation.set_room(""), "Precondition failure: room cannot be empty");
}

TEST_F(RenovationsDomainTest, ChronologicalOrder) {
    testRenovation.set_start("12:00");
    testRenovation.set_end("10:00");

    EXPECT_EQ(testRenovation.get_start(), "12:00");
    EXPECT_EQ(testRenovation.get_end(), "10:00");
}

string formatRenovation(const Renovations& r) {
    return "Room " + r.get_room() + ": " + r.get_start() + " - " + r.get_end();
}

TEST(RenovationsOutputTest, OutputFormatCorrectness) {
    Renovations r;
    r.set_room("G.0.05");
    r.set_start("09:00");
    r.set_end("12:00");

    string expected = "Room G.0.05: 09:00 - 12:00";
    EXPECT_EQ(formatRenovation(r), expected);
}

TEST(RenovationsInputTest, InputLegalData) {
    Renovations r;
    string fileInputRoom = "Auditorium 1";

    r.set_room(fileInputRoom);
    EXPECT_EQ(r.get_room(), "Auditorium 1");
}

TEST(RenovationsInputTest, InputInvalidTimeFormat) {
    Renovations r;
    string badTime = "25:61";

    r.set_start(badTime);
    EXPECT_EQ(r.get_start(), "25:61");
}