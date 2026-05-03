/*
* Korte beschrijving:
*Dit stelt onze Testen voor.
*
* @authors Bruno Luango en Ibrahim Akiyev
* @date 11/03/2026
* @version 1.0
*/

// Include blok
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

// Globale using statements
using namespace std;

int main(int argc, char **argv) {
    std::cout<<"starten van de testen in main..."<<std::endl;
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
    return 0;
}

// PARSER TESTS

// --- PARSE ELEMENT TESTS ---

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

// --- ONTBREKENDE CONTRACT VIOLATIONS VOOR PARSE FUNCTIES ---
TEST(ParserTest, ParseElement_NullPointers) {
    Parser p;
    // Test of alle nieuwe parse functies de REQUIRE(element != NULL) check hebben
    EXPECT_DEATH(p.parse_campus_element(nullptr), ".*");
    EXPECT_DEATH(p.parse_building_element(nullptr), ".*");
    EXPECT_DEATH(p.parse_renovation_element(nullptr), ".*");
    EXPECT_DEATH(p.parse_catering_element(nullptr), ".*");
}

TEST(ParserTest, GetFilename_HappyDay) {
    Parser p;
    string naam = "mijnBestand.xml";

    // We gaan ervan uit dat je een setter hebt of de naam via de constructor zet
    p.set_filename(naam);

    EXPECT_EQ(p.get_filename(), naam);
}

TEST(ParserTest, GetFilename_Boundaries) {
    Parser p;

    // Randgeval: Minimum lengte (1 karakter)
    p.set_filename("a");
    EXPECT_EQ(p.get_filename(), "a");

    // Randgeval: Spaties en vreemde tekens
    p.set_filename("test file @ v2.txt");
    EXPECT_EQ(p.get_filename(), "test file @ v2.txt");
}

TEST(ParserTest, GetFilename_ContractViolation) {
    Parser p;

    // Zorg dat de filename leeg is (meestal de default status)
    // p.set_filename("");

    // We verwachten dat het programma stopt met de foutmelding uit je REQUIRE
    EXPECT_DEATH(p.get_filename(), "Preconditie gefaald: filename mag niet leeg zijn");
}

TEST(ParserTest, SetFilename_HappyDay) {
    Parser p;
    string nieuweNaam = "config.xml";

    p.set_filename(nieuweNaam);

    // We gebruiken de getter om te zien of de setter zijn werk deed
    EXPECT_EQ(p.get_filename(), nieuweNaam);
}


TEST(ParserTest, SetFilename_Boundaries) {
    Parser p;

    // Randgeval: kortst mogelijke naam
    p.set_filename("z");
    EXPECT_EQ(p.get_filename(), "z");

    // Randgeval: naam met spaties (technisch niet leeg, dus het mag)
    p.set_filename("   ");
    EXPECT_EQ(p.get_filename(), "   ");
}


TEST(ParserTest, SetFilename_ContractViolation) {
    Parser p;
    string legeNaam = "";

    // We verwachten een crash met de specifieke foutmelding uit je REQUIRE
    EXPECT_DEATH(p.set_filename(legeNaam), "Preconditie gefaald: nieuwe filename mag niet leeg zijn");
}


TEST(ParserTest, SetFilename_Overwrite) {
    Parser p;
    p.set_filename("oud.xml");
    p.set_filename("nieuw.xml"); // Overschrijven

    EXPECT_EQ(p.get_filename(), "nieuw.xml");
}


TEST(ParserTest, XmlToDoc_HappyDay) {
    Parser p;
    // Zorg dat "valid.xml" echt bestaat in je testmap!
    p.set_filename("../Tests/test_XML_file/happy_day.xml");

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();

    // Check of het document geen fouten bevat na het laden
    EXPECT_FALSE(doc.Error());
}


TEST(ParserTest, XmlToDoc_EmptyFile) {
    Parser p;
    p.set_filename("../Tests/test_XML_file/rootless.xml"); // Een bestand van 0 bytes

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    // TinyXML geeft meestal een error bij een compleet leeg bestand
    EXPECT_TRUE(doc.Error());
}

TEST(ParserTest, XmlToDoc_InvalidXML) {
    Parser p;
    p.set_filename("not_a_xml.txt"); // Bestand met willekeurige tekst

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    EXPECT_TRUE(doc.Error());
}


// De verplichte ContractViolation test
TEST(ParserTest, XmlToDoc_ContractViolation) {
    Parser p;
    // We gaan ervan uit dat de default filename leeg is
    EXPECT_DEATH(p.Xml_to_TiXmlDocument(), "Preconditie gefaald: filename mag niet leeg zijn");
}

// Test voor ontbrekend bestand (I/O issue)
TEST(ParserTest, XmlToDoc_MissingFile) {
    Parser p;
    p.set_filename("bestaat_niet.xml");

    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    EXPECT_TRUE(doc.Error()); // De doc moet een error-status hebben
}


TEST(ParserTest, FileErrorCheck_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("../Tests/test_XML_file/happy_day.xml"); // Zorg dat dit bestand bestaat

    int result = p.file_error_check(doc);

    EXPECT_EQ(result, 0); // 0 staat voor succes
    EXPECT_FALSE(doc.Error()); // TinyXML zelf mag ook geen fout melden
}


TEST(ParserTest, FileErrorCheck_EmptyFile) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("../Tests/test_XML_file/rootless.xml");

    int result = p.file_error_check(doc);

    // Een compleet leeg bestand is technisch gezien geen geldige XML
    EXPECT_EQ(result, 1);
}

TEST(ParserTest, FileErrorCheck_CorruptXML) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("corrupt.xml"); // Bestand met bijv. <tag> zonder </tag>

    int result = p.file_error_check(doc);

    EXPECT_EQ(result, 1);
}


TEST(ParserTest, FileErrorCheck_MissingFile) {
    Parser p;
    TiXmlDocument doc;
    p.set_filename("non_existent_file_999.xml");

    int result = p.file_error_check(doc);

    EXPECT_EQ(result, 1); // Moet falen (1)
}

TEST(ParserTest, FileErrorCheck_ContractViolation) {
    Parser p;
    TiXmlDocument doc;
    // We zetten GEEN filename (blijft leeg)

    // Controleer of de REQUIRE de boel blokkeert
    EXPECT_DEATH(p.file_error_check(doc), "Preconditie gefaald: filename mag niet leeg zijn");
}


TEST(ParserTest, IfRootExists_HappyDay) {
    Parser p;
    TiXmlElement root("MyRoot"); // We maken een geldig element aan

    int result = p.if_root_exists(&root);

    EXPECT_EQ(result, 0); // 0 staat voor succes (root bestaat)
}


TEST(ParserTest, IfRootExists_NullPointer) {
    Parser p;
    TiXmlElement* legeRoot = NULL;

    int result = p.if_root_exists(legeRoot);

    EXPECT_EQ(result, 1); // 1 staat voor failure (geen root gevonden)
}

TEST(ParserTest, IfRootExists_Robustness) {
    Parser p;
    // Test of de functie consistent blijft bij meerdere verschillende aanroepen
    EXPECT_EQ(p.if_root_exists(NULL), 1);

    TiXmlElement root("Test");
    EXPECT_EQ(p.if_root_exists(&root), 0);
}


TEST(ParserTest, MakeRoot_HappyDay) {
    Parser p;
    TiXmlDocument doc;
    // We simuleren een geladen document
    doc.Parse("<system><subelement/></system>");

    TiXmlElement* root = p.make_root(doc);

    ASSERT_NE(root, nullptr); // Root mag niet NULL zijn
    EXPECT_STREQ(root->Value(), "system"); // Check of het de juiste tag is
}


TEST(ParserTest, MakeRoot_EmptyDocument) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse(""); // Helemaal leeg

    TiXmlElement* root = p.make_root(doc);

    EXPECT_EQ(root, nullptr); // Er is geen FirstChildElement
}

TEST(ParserTest, MakeRoot_OnlyComments) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("");

    TiXmlElement* root = p.make_root(doc);

    EXPECT_EQ(root, nullptr); // Commentaar is geen TiXmlElement
}


TEST(ParserTest, MakeRoot_AfterFileError) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<open-tag-zonder-sluiting"); // Veroorzaakt een error

    ASSERT_TRUE(doc.Error()); // Bevestig dat er een error is (preconditie geschonden)

    TiXmlElement* root = p.make_root(doc);
    EXPECT_EQ(root, nullptr);
}


TEST(ParserTest, MakeRoot_CorrectElement) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<eerste>...</eerste><tweede>...</tweede>");

    TiXmlElement* root = p.make_root(doc);

    EXPECT_STREQ(root->Value(), "eerste"); // Moet echt de EERSTE zijn
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
    // We laten CAPACITY weg
    doc.Parse("<ROOM><NAME>Aula</NAME><IDENTIFIER>A.01</IDENTIFIER></ROOM>");
    TiXmlElement* room_el = doc.FirstChildElement("ROOM");

    Room r = p.parse_room_element(room_el);

    // Omdat CAPACITY ontbreekt, moet alles op "Fout"/0 springen volgens jouw logica
    EXPECT_EQ(r.get_name(), "Fout");
    EXPECT_EQ(r.get_capacity(), 0);
}

TEST(ParserTest, ParseRoom_EmptyTags) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<ROOM><NAME></NAME><IDENTIFIER>A.01</IDENTIFIER><CAPACITY>100</CAPACITY></ROOM>");
    TiXmlElement* room_el = doc.FirstChildElement("ROOM");

    Room r = p.parse_room_element(room_el);
    EXPECT_EQ(r.get_name(), "Fout"); // Lege string wordt "Fout"
}


TEST(ParserTest, ParseRoom_InvalidCapacity) {
    Parser p;
    TiXmlDocument doc;
    doc.Parse("<ROOM><NAME>Lab</NAME><IDENTIFIER>L.01</IDENTIFIER><CAPACITY>abc</CAPACITY></ROOM>");
    TiXmlElement* room_el = doc.FirstChildElement("ROOM");

    Room r = p.parse_room_element(room_el);
    EXPECT_EQ(r.get_capacity(), 0);
    EXPECT_EQ(r.get_name(), "Fout"); // Volgens jouw check: als één ding fout is, is alles fout
}


TEST(ParserTest, ParseRoom_ContractViolation) {
    Parser p;
    // Preconditie check: mag niet NULL zijn
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
    // We laten DATE weg
    doc.Parse("<MEETING><LABEL>Test</LABEL><IDENTIFIER>ID</IDENTIFIER><ROOM>A1</ROOM></MEETING>");
    TiXmlElement* meet_el = doc.FirstChildElement("MEETING");

    Meeting m = p.parse_meeting_element(meet_el);

    // Omdat één veld ontbreekt, wordt alles "fout" gezet door je laatste if-check
    EXPECT_EQ(m.get_label(), "fout");
    EXPECT_EQ(m.get_date(), "fout");
}


TEST(ParserTest, ParseMeeting_EmptyTagHandling) {
    Parser p;
    TiXmlDocument doc;
    // Een lege <LABEL> geeft NULL bij .GetText()
    doc.Parse("<MEETING><LABEL></LABEL><IDENTIFIER>ID</IDENTIFIER><ROOM>A1</ROOM><DATE>Today</DATE></MEETING>");
    TiXmlElement* meet_el = doc.FirstChildElement("MEETING");

    // Actie: voer de parse uit
    Meeting m = p.parse_meeting_element(meet_el);

    // Verificatie: De code mag niet crashen en moet "fout" teruggeven
    // omdat LABEL leeg was.
    EXPECT_EQ(m.get_label(), "fout");
    EXPECT_EQ(m.get_identifier(), "fout"); // Alles wordt "fout" in jouw logica
}


TEST(ParserTest, ParseMeeting_ContractViolation) {
    Parser p;
    // Preconditie: mag niet NULL zijn
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
    // USER is leeg, MEETING is aanwezig
    doc.Parse("<PARTICIPATION><USER></USER><MEETING>M001</MEETING></PARTICIPATION>");
    TiXmlElement* el = doc.FirstChildElement("PARTICIPATION");

    Participation part = p.parse_participation_element(el);

    // Omdat USER leeg is, moet alles volgens jouw logica "fout" worden
    EXPECT_EQ(part.get_user(), "fout");
    EXPECT_EQ(part.get_meeting(), "fout");
}


TEST(ParserTest, ParseParticipation_MissingTags) {
    Parser p;
    TiXmlDocument doc;
    // Volledig ontbrekende MEETING tag
    doc.Parse("<PARTICIPATION><USER>Jan</USER></PARTICIPATION>");
    TiXmlElement* el = doc.FirstChildElement("PARTICIPATION");

    Participation part = p.parse_participation_element(el);

    EXPECT_EQ(part.get_meeting(), "fout");
    EXPECT_EQ(part.get_user(), "fout");
}


TEST(ParserTest, ParseParticipation_NullPointer) {
    Parser p;
    // We verwachten dat het programma stopt met de specifieke REQUIRE melding
    EXPECT_DEATH(p.parse_participation_element(NULL), "Preconditie gefaald: participation_element mag niet NULL zijn");
}


TEST(ParserTest, RunThroughElement_HappyDay) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    // We testen met 2 kamers
    doc.Parse("<ROOT><ROOM><NAME>A1</NAME><IDENTIFIER>ID1</IDENTIFIER><CAPACITY>10</CAPACITY></ROOM>"
              "<ROOM><NAME>B2</NAME><IDENTIFIER>ID2</IDENTIFIER><CAPACITY>20</CAPACITY></ROOM></ROOT>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    p.run_trough_Element("ROOM", root, planner);

    // Check Kardinaliteit: zijn er 2 kamers toegevoegd?
    // (Gevat in een getter van je planner, bijv. getRooms().size())
    EXPECT_EQ(planner.getRooms().size(), 2ULL);
}





TEST(ParserTest, RunThroughElement_SkipErrors) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    // Eén goede kamer, één kamer met foutieve data (lege naam)
    doc.Parse("<ROOT><ROOM><NAME>Goed</NAME><IDENTIFIER>I1</IDENTIFIER><CAPACITY>10</CAPACITY></ROOM>"
              "<ROOM><NAME></NAME><IDENTIFIER>I2</IDENTIFIER><CAPACITY>10</CAPACITY></ROOM></ROOT>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    p.run_trough_Element("ROOM", root, planner);

    // Er zou slechts 1 kamer in de planner moeten zitten
    EXPECT_EQ(planner.getRooms().size(), 1ULL);
}


TEST(ParserTest, RunThroughElement_InvalidTagName) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    doc.Parse("<ROOT/>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    // "AUTO" is geen geldige tag volgens je REQUIRE
    EXPECT_DEATH(p.run_trough_Element("AUTO", root, planner), "Element moet .* zijn");
}

TEST(ParserTest, RunThroughElement_NullRoot) {
    Parser p;
    MeetingPlanner planner;

    // Root is NULL
    EXPECT_DEATH(p.run_trough_Element("ROOM", NULL, planner), "root moet bestaan");
}

TEST(ParserTest, RunThroughElement_MeetingKardinaliteit) {
    Parser p;
    MeetingPlanner planner;
    TiXmlDocument doc;
    doc.Parse("<ROOT><MEETING><LABEL>A</LABEL><IDENTIFIER>1</IDENTIFIER><ROOM>R1</ROOM><DATE>D1</DATE></MEETING></ROOT>");
    TiXmlElement* root = doc.FirstChildElement("ROOT");

    p.run_trough_Element("MEETING", root, planner);
    // Verifieer of de meeting is toegevoegd
    EXPECT_EQ(planner.getMeetings().size(), 1ULL);
}



class BuildingsDomainTest : public ::testing::Test {
protected:
    Buildings testBuilding;
};

// Happy Day Scenario
TEST_F(BuildingsDomainTest, HappyDaySettersGetters) {
    testBuilding.set_name("G-gebouw");
    testBuilding.set_identifier("G.1.01");
    testBuilding.set_campus("Middelheim");

    EXPECT_EQ(testBuilding.get_name(), "G-gebouw");
    EXPECT_EQ(testBuilding.get_identifier(), "G.1.01");
    EXPECT_EQ(testBuilding.get_campus(), "Middelheim");
}

TEST_F(BuildingsDomainTest, BoundaryEmptyStrings) {
    testBuilding.set_name("");
    EXPECT_TRUE(testBuilding.get_name().empty());

    testBuilding.set_identifier("");
    EXPECT_TRUE(testBuilding.get_identifier().empty());
}

// Grondig: Wijzigen van bestaande waarden (Postconditie check)
TEST_F(BuildingsDomainTest, OverwriteValues) {
    testBuilding.set_name("Oud");
    testBuilding.set_name("Nieuw");
    EXPECT_EQ(testBuilding.get_name(), "Nieuw");
}

// Veronderstelde helper functie voor de test
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
    // Simuleer data die uit een bestand komt
    std::string inputName = "C-gebouw";
    std::string inputID = "C.0.01";
    std::string inputCampus = "Groenenborger";

    Buildings b;
    b.set_name(inputName);
    b.set_identifier(inputID);
    b.set_campus(inputCampus);

    // Verifieer of de invoer correct is verwerkt in het domeinobject
    EXPECT_EQ(b.get_campus(), "Groenenborger");
}

TEST(BuildingsInputTest, InputSpecialCharacters) {
    Buildings b;
    // Testen met speciale karakters (accenten, spaties)
    b.set_name("Bâtiment-X 2.0");
    EXPECT_EQ(b.get_name(), "Bâtiment-X 2.0");
}



// CATEGORIE: RANDGEVALLEN - BEREIK
TEST_F(BuildingsDomainTest, TestExtremeStringLength) {
    std::string longName(5000, 'A');
    testBuilding.set_name(longName);
    EXPECT_EQ(testBuilding.get_name().length(), 5000u);
}



class CampusDomainTest : public ::testing::Test {
protected:
    Campus testCampus;
};

// --- ALGEMENE CORRECTHEID (Happy Day) ---
TEST_F(CampusDomainTest, HappyDaySettersGetters) {
    testCampus.set_name("Middelheim");
    testCampus.set_identifier("CMI");

    EXPECT_EQ(testCampus.get_name(), "Middelheim");
    EXPECT_EQ(testCampus.get_identifier(), "CMI");
}

// --- RANDGEVALLEN: BESTAAN ---
TEST_F(CampusDomainTest, BoundaryEmptyStrings) {
    // Testen van lege strings (Bestaan)
    // Merk op: De preconditie zegt dat de naam niet leeg mag zijn.
    testCampus.set_name("");
    EXPECT_EQ(testCampus.get_name().length(), 0u);
}

// --- RANDGEVALLEN: ORDE ---
TEST_F(CampusDomainTest, TestOrderOfOperations) {
    // Heeft de volgorde van setten effect op het resultaat?
    testCampus.set_identifier("GGB");
    testCampus.set_name("Groenenborger");

    EXPECT_EQ(testCampus.get_name(), "Groenenborger");
    EXPECT_EQ(testCampus.get_identifier(), "GGB");
}

// --- RANDGEVALLEN: BEREIK ---
TEST_F(CampusDomainTest, TestLongStringRange) {
    // Hoe reageert het component op een maximum/grote waarde?
    std::string longName(1000, 'A');
    testCampus.set_name(longName);
    EXPECT_EQ(testCampus.get_name().length(), 1000u);
}

// Veronderstel een simpele weergave-functie voor de presentatielaag
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

// --- FOUTEN: I/O ISSUES & ONVOLLEDIGHEID ---
TEST(CampusInputTest, InputMissingData) {
    Campus c;
    // Wat als de input-file een lege identifier geeft? (Kardinaliteit/Bestaan)
    std::string inputID = "";
    c.set_identifier(inputID);

    // Verifieer of het systeem hiermee om kan gaan zonder te crashen
    EXPECT_TRUE(c.get_identifier().empty());
}

TEST(CampusInputTest, InputSpecialCharacters) {
    Campus c;
    // Testen van vreemde karakters in namen (Randgeval: Bereik van karakters)
    c.set_name("Campus @ Stadscampus #1");
    EXPECT_EQ(c.get_name(), "Campus @ Stadscampus #1");
}



class CateringprovidersDomainTest : public ::testing::Test {
protected:
    Cateringproviders testProvider;
};

// --- ALGEMENE CORRECTHEID (Happy Day) ---
TEST_F(CateringprovidersDomainTest, HappyDaySettersGetters) {
    testProvider.set_campus("Campus Middelheim");
    testProvider.set_co2(15.5f);

    EXPECT_EQ(testProvider.get_campus(), "Campus Middelheim");
    EXPECT_FLOAT_EQ(testProvider.get_co2(), 15.5f);
}

// --- RANDGEVALLEN: BEREIK (Numeriek) ---
TEST_F(CateringprovidersDomainTest, TestCO2PreconditionViolation) {
    // Gebruik EXPECT_DEATH omdat REQUIRE een abort() triggert, geen exception.
    // We controleren ook of de juiste foutmelding in stderr verschijnt.
    EXPECT_DEATH(testProvider.set_co2(0.0f), "Precondition failure: Value must be greater then zero");

    // Test ook een negatieve waarde
    EXPECT_DEATH(testProvider.set_co2(-1.0f), "Precondition failure: Value must be greater then zero");
}

// --- RANDGEVALLEN: BESTAAN (Strings) ---
TEST_F(CateringprovidersDomainTest, BoundaryEmptyCampus) {
    // De actie die de crash (abort) veroorzaakt MOET binnen EXPECT_DEATH staan.
    // We controleren ook of de specifieke foutboodschap uit je REQUIRE wordt getoond.
    EXPECT_DEATH(testProvider.set_campus(""), "Precondition failure: campus cannot be empty");
}
// --- FOUTEN: CONTRACT VIOLATIONS ---
TEST_F(CateringprovidersDomainTest, NegativeCO2Violation) {
    // We testen opzettelijk een foutieve waarde om te verifiëren
    // dat het systeem correct omgaat met fouten (volgens Appendix A).

    // Gebruik EXPECT_DEATH omdat REQUIRE een abort() aanroept.
    // We controleren of het programma stopt met de juiste foutmelding.
    EXPECT_DEATH(testProvider.set_co2(-10.0f), "Precondition failure: Value must be greater then zero");
}

TEST_F(CateringprovidersDomainTest, ZeroCO2Violation) {
    // Randgeval: Bereik (exact nul).
    // Omdat de preconditie "bigger then 0" is, moet 0.0f ook falen via REQUIRE.

    // We gebruiken EXPECT_DEATH omdat REQUIRE een abort() triggert in plaats van een exception.
    EXPECT_DEATH(testProvider.set_co2(0.0f), "Precondition failure: Value must be greater then zero");
}

// Helper voor de presentatielaag
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

TEST(CateringprovidersInputTest, InputInvalidData) {
    Cateringproviders p;

    // Simuleer een situatie waarbij de invoer ontbreekt (Bestaan randgeval)
    string invalidInputCampus = "";

    // De actie die de REQUIRE (en dus de abort) triggert moet binnen EXPECT_DEATH staan
    // We controleren op de specifieke foutmelding die je REQUIRE geeft
    EXPECT_DEATH(p.set_campus(invalidInputCampus), "Precondition failure: campus cannot be empty");
}

TEST(CateringprovidersInputTest, InputLargeNumericalValue) {
    Cateringproviders p;
    // Test de verwerking van een extreem hoge CO2 waarde (Bereik: Maximum)
    float maxCO2 = 1000000.0f;
    p.set_co2(maxCO2);
    EXPECT_FLOAT_EQ(p.get_co2(), 1000000.0f);
}



class RenovationsDomainTest : public ::testing::Test {
protected:
    Renovations testRenovation;
};

// --- ALGEMENE CORRECTHEID (Happy Day) ---
TEST_F(RenovationsDomainTest, HappyDaySettersGetters) {
    testRenovation.set_room("L.1.01");
    testRenovation.set_start("08:00");
    testRenovation.set_end("17:00");

    EXPECT_EQ(testRenovation.get_room(), "L.1.01");
    EXPECT_EQ(testRenovation.get_start(), "08:00");
    EXPECT_EQ(testRenovation.get_end(), "17:00");
}

// --- RANDGEVALLEN: BESTAAN ---
TEST_F(RenovationsDomainTest, EmptyRoomViolation) {
    // EXPECT_DEATH controleert of het programma afsluit met een foutmelding
    // bij een schending van de REQUIRE preconditie.
    EXPECT_DEATH(testRenovation.set_room(""), "Precondition failure: room cannot be empty");
}

// --- RANDGEVALLEN: ORDE ---
TEST_F(RenovationsDomainTest, ChronologicalOrder) {
    // Een renovatie kan logischerwijs niet eindigen voordat deze begint.
    // Zelfs als de klasse dit nog niet checkt, is dit een essentieel scenario om te testen.
    testRenovation.set_start("12:00");
    testRenovation.set_end("10:00");

    // In een uitgebreider systeem zou je hier een waarschuwing of exception verwachten.
    // Voor nu controleren we of de data op zijn minst correct is opgeslagen.
    EXPECT_EQ(testRenovation.get_start(), "12:00");
    EXPECT_EQ(testRenovation.get_end(), "10:00");
}

// Veronderstelde weergave-functie
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
    // Simuleer input vanuit een bestand (bijv. image_0c54a7.png).
    string fileInputRoom = "Auditorium 1";

    r.set_room(fileInputRoom);
    EXPECT_EQ(r.get_room(), "Auditorium 1");
}

// --- RANDGEVALLEN: BEREIK & FOUTEN ---
TEST(RenovationsInputTest, InputInvalidTimeFormat) {
    Renovations r;
    // Wat als het bestand een ongeldig tijdformaat bevat?
    string badTime = "25:61";

    // Controleer of de set_start precondities dit opvangen of dat het object de data accepteert.
    r.set_start(badTime);
    EXPECT_EQ(r.get_start(), "25:61");
}