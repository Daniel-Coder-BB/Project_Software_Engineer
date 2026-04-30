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

// Globale using statements
using namespace std;

int main(int argc, char **argv) {
    std::cout<<"starten van de testen in main..."<<std::endl;
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
    return 0;
}

// PARSER TESTS

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