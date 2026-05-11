#include <gtest/gtest.h>
#include "../tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "../Classes/Parser/Parser.h"
#include "../Classes/Meetingplanner/Meetingplanner.h"

using namespace std;

class ParserInputTest : public ::testing::Test {
protected:
    Parser p;
    MeetingPlanner planner;
};

// ============================================================================
// 1. ALGEMENE CORRECTHEID (Happy Day)
// ============================================================================
TEST_F(ParserInputTest, InputHappyDay_Parser) {
    p.set_filename("../testInput/happy_day_parser.xml");
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();

    // Controleert of het systeem onder normale omstandigheden doet wat het moet
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(p.file_error_check(doc), 0);

    TiXmlElement* root = p.make_root(doc);
    ASSERT_NE(root, nullptr);

    // Verifieer of de data correct in de planner terechtkomt
    p.run_trough_Element("ROOM", root, planner);
    // Gebruik 0ULL om signed/unsigned mismatch te voorkomen
    EXPECT_GT(planner.getRooms().size(), 0ULL);
}

// ============================================================================
// 2. RANDGEVALLEN (Bestaan, Bereik & Kardinaliteit)
// ============================================================================

// BESTAAN: Wat met lege strings of ontbrekende tags?
TEST_F(ParserInputTest, InputMissingFields_Bestaan) {
    p.set_filename("../testInput/missing_fields.xml");
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    TiXmlElement* root = p.make_root(doc);

    TiXmlElement* roomEl = root->FirstChildElement("ROOM");
    Room r = p.parse_room_element(roomEl);

    // De parser moet "Fout" teruggeven bij ontbrekende data
    EXPECT_EQ(r.get_name(), "Fout");
    EXPECT_EQ(r.get_capacity(), 0);
}

// BEREIK: Hoe reageert het component op nul, negatieve waarden of foute types?
TEST_F(ParserInputTest, InputInvalidTypes_Bereik) {
    p.set_filename("../testInput/invalid_types.xml");
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();
    TiXmlElement* root = p.make_root(doc);

    // Test Room met ongeldige capaciteit (tekst i.p.v. getal)
    TiXmlElement* roomEl = root->FirstChildElement("ROOM");
    Room r = p.parse_room_element(roomEl);
    EXPECT_EQ(r.get_capacity(), 0);

    // Test Catering met negatieve CO2 (minimum overschreden)
    TiXmlElement* cateringEl = root->FirstChildElement("CATERING");
    Cateringproviders c = p.parse_catering_element(cateringEl);
    EXPECT_EQ(c.get_campus(), "fout");
}

// KARDINALITEIT: Wat is het verwachte aantal items bij een lege lijst?
TEST_F(ParserInputTest, InputEmptyList_Kardinaliteit) {
    TiXmlDocument doc;
    doc.Parse("<SYSTEM></SYSTEM>"); // Geen elementen binnen de root
    TiXmlElement* root = doc.FirstChildElement("SYSTEM");

    p.run_trough_Element("MEETING", root, planner);
    // Gebruik 0ULL om signed/unsigned mismatch te voorkomen
    EXPECT_EQ(planner.getMeetings().size(), 0ULL);
}

// ============================================================================
// 3. FOUTEN (I/O Issues & Syntax)
// ============================================================================

// FOUTEN: Ontbrekende of onleesbare bestanden
TEST_F(ParserInputTest, InputNonExistingFile_Fouten) {
    p.set_filename("../testInput/bestaat_niet.xml");
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();

    // Verifieer dat het systeem correct omgaat met I/O fouten
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(p.file_error_check(doc), 1);
}

// FOUTEN: XML Syntax fouten (niet-well-formed XML)
TEST_F(ParserInputTest, InputSyntaxError_Fouten) {
    p.set_filename("../testInput/syntax_error.xml");
    TiXmlDocument doc = p.Xml_to_TiXmlDocument();

    EXPECT_TRUE(doc.Error());
    TiXmlElement* root = p.make_root(doc);
    EXPECT_EQ(root, nullptr); // Root mag niet bestaan bij syntax fout
}

// ============================================================================
// 4. CONTRACT VIOLATIONS (Onafhankelijk & Grondig)
// ============================================================================
TEST_F(ParserInputTest, InputNullPtr_ContractViolation) {
    // Grondig testen: ALLE precondities controleren
    EXPECT_DEATH(p.parse_room_element(nullptr), "room_element mag niet NULL zijn");
    EXPECT_DEATH(p.parse_meeting_element(nullptr), "meeting_element mag niet NULL zijn");
}