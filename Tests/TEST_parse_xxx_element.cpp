/*
* Korte beschrijving:
*Dit stelt onze Testen voor.
*
* @authors Bruno Luango en Ibrahim Akiyev
* @date 11/03/2026
* @version 1.0
*/

// Include blok
#include <gtest/gtest.h>
#include <iostream>
#include "tinyxml.h"
#include "Classes/Room/Room.h"
#include "Classes/Meeting/Meeting.h"
#include <gtest/gtest.h>
#include <pstl/execution_defs.h>
#include "Classes/Meeting/Meeting.h"
#include "Classes/Participation/Participation.h"
#include <Classes/Meetingplanner/Meetingplanner.h>
#include "Classes/Parser/Parser.h"

// Globale using statements
using namespace std;



//body-gedeelte
/*
 *This function parses the room tag of an XML file
 *@param room_element an XML element with the ROOM tag
 *@return new_room a room of the type ROOM with all the details
 */
Room t_parse_room_element(TiXmlElement* room_element) {
    Room new_room;
    new_room.set_identifier("Fout");
    new_room.set_name("Fout");
    new_room.set_capacity(0);
    if (room_element->FirstChildElement("NAME")) {
        string new_name = room_element->FirstChildElement("NAME")->GetText();
        if (new_name.empty()) {
            new_room.set_name("Fout");
        }
        else {
            new_room.set_name(new_name);
        }
    }
    if (room_element->FirstChildElement("IDENTIFIER")) {
        string new_id = room_element->FirstChildElement("IDENTIFIER")->GetText();
        if (new_id.empty()) {
            new_room.set_identifier("Fout");
        }
        else {
            new_room.set_identifier(new_id);
        }
    }
    if (room_element->FirstChildElement("CAPACITY")) {
        // Omzetten van string naar int
        try {
            int capacity = std::stoi(room_element->FirstChildElement("CAPACITY")->GetText());
            new_room.set_capacity(capacity);
        }
        catch (const std::invalid_argument& e) {
            cerr<<"Capacity moet een getal zijn";
            new_room.set_capacity(0);
        }

    }
    if (new_room.get_name() == "Fout" or new_room.get_identifier()=="Fout" or new_room.get_capacity() == 0) {
        new_room.set_capacity(0);
        new_room.set_name("Fout");
        new_room.set_identifier("Fout");
    }

    return new_room;
}

/*
 *This function parses the meeting tag of an XML file
 *@param meeting_element an XML element with the MEETING tag
 *@return new_meeting a meeting of the type MEETING with all the details
 */
Meeting t_parse_meeting_element(TiXmlElement* meeting_element) {
    Meeting new_meeting;
    new_meeting.set_date("Fout");
    new_meeting.set_identifier("Fout");
    new_meeting.set_label("Fout");
    new_meeting.set_room("Fout");
    if (meeting_element->FirstChildElement("LABEL")) {
        new_meeting.set_label(meeting_element->FirstChildElement("LABEL")->GetText());
    }
    if (meeting_element->FirstChildElement("IDENTIFIER")) {
        new_meeting.set_identifier(meeting_element->FirstChildElement("IDENTIFIER")->GetText());
    }
    if (meeting_element->FirstChildElement("ROOM")) {
        new_meeting.set_room(meeting_element->FirstChildElement("ROOM")->GetText());
    }

    if (meeting_element->FirstChildElement("DATE")) {
        new_meeting.set_date(meeting_element->FirstChildElement("DATE")->GetText());

    }
    if (new_meeting.get_label() == "Fout" or new_meeting.get_identifier()=="Fout" or new_meeting.get_room()=="Fout" or new_meeting.get_date()=="Fout") {
        new_meeting.set_label("fout");
        new_meeting.set_identifier("fout");
        new_meeting.set_room("fout");
        new_meeting.set_date("fout");
    }
    return new_meeting;
}


/*
 *This function parses the participation tag of an XML file
 *@param participation_element an XML element with the PARTICIPATION tag
 *@return new_participation a participation of the type PARTICIPATION with all the details
 */
Participation t_parse_participation_element(TiXmlElement* participation_element) {
    Participation new_participation;
    new_participation.set_meeting("Fout");
    new_participation.set_user("Fout");
    if (participation_element->FirstChildElement("USER")) {
        new_participation.set_user(participation_element->FirstChildElement("USER")->GetText());
    }
    if (participation_element->FirstChildElement("MEETING")) {
        new_participation.set_meeting(participation_element->FirstChildElement("MEETING")->GetText());
    }
    if (new_participation.get_meeting() == "Fout" or new_participation.get_user()=="Fout") {
        new_participation.set_meeting("fout");
        new_participation.set_user("fout");

    }



    return new_participation;
}


/*
 *This function checks if an error happens with reading the file
 *@param filename The directory where the file is
 *@param doc a TiXmlDocument wich contains our XML file
 *@return if failed (1) or if no errors(0)
 */
int t_file_error_check(const string& filename,TiXmlDocument& doc) {

    if (!doc.LoadFile(filename.c_str())) {
        cerr << "Fout bij laden: " << doc.ErrorDesc() << endl;
        return 1;
    }
    return 0;
}


int t_if_root_exists(TiXmlElement* root) {
    if (root == NULL) {
        cerr << "Geen root element gevonden." << endl;
        return 1;
    }
    return 0;
}


int main(int argc, char **argv) {
    std::cout<<"starten van de testen in main..."<<std::endl;
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
    return 0;
}

TEST(file_error_check_test,happy_day_test) {
    TiXmlDocument test_xml_doc;
    string test_xml_directory = "../Tests/test_XML_file/happy_day.xml";
    EXPECT_EQ(t_file_error_check(test_xml_directory,test_xml_doc),0);
}

TEST(file_error_check_test,file_not_loading_test) {
    TiXmlDocument test_doc;
    string test_filename = "happy_day.xml";
    EXPECT_EQ(t_file_error_check(test_filename,test_doc),1);

}

TEST(t_if_root_exists,happy_day_test_has_root) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/happy_day.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement();
    EXPECT_EQ(t_if_root_exists(test_root),0);

}

TEST(t_if_root_exists,happy_day_test_has_no_root) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/rootless.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement();
    EXPECT_EQ(t_if_root_exists(test_root),1);

}

TEST(t_parse_room_element,happy_day_test) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/happy_day.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    Room room;
    room.set_name("M.G.023");
    room.set_identifier("Room98732");
    room.set_capacity(10);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* test_room = test_root->FirstChildElement("ROOM"); test_room != NULL; test_room = test_room->NextSiblingElement("ROOM")) {
        EXPECT_EQ(t_parse_room_element(test_room),room);


    }
}

TEST(t_parse_room_element,missing_information_test) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/missing_information.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    Room room;
    room.set_name("Fout");
    room.set_identifier("Fout");
    room.set_capacity(0);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* test_room = test_root->FirstChildElement("ROOM"); test_room != NULL; test_room = test_room->NextSiblingElement("ROOM")) {
        EXPECT_EQ(t_parse_room_element(test_room),room);


    }
}

TEST(t_parse_room_element,capacity_not_integer_test) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/capacity_not_int.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    Room room;
    room.set_name("Fout");
    room.set_identifier("Fout");
    room.set_capacity(0);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* test_room = test_root->FirstChildElement("ROOM"); test_room != NULL; test_room = test_room->NextSiblingElement("ROOM")) {
        EXPECT_EQ(t_parse_room_element(test_room),room);


    }
}


 TEST(test_parse_meeting_element, Happy_day_test) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/happy_day.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    Meeting meeting;
    meeting.set_label("Weekly meeting");
    meeting.set_identifier("Meeting_478463");
    meeting.set_room("Room98732");
    meeting.set_date("2026-05-22");

    for (TiXmlElement* test_meeting = test_root->FirstChildElement("MEETING"); test_meeting != NULL; test_meeting = test_meeting->NextSiblingElement("MEETING")) {
        EXPECT_EQ(t_parse_meeting_element(test_meeting),meeting);
    }
}

TEST(test_parse_meeting_element, missing_information_test) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/missing_information.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    Meeting meeting;
    meeting.set_label("fout");
    meeting.set_identifier("fout");
    meeting.set_room("fout");
    meeting.set_date("fout");

    for (TiXmlElement* test_meeting = test_root->FirstChildElement("MEETING"); test_meeting != NULL; test_meeting = test_meeting->NextSiblingElement("MEETING")) {
        EXPECT_EQ(t_parse_meeting_element(test_meeting),meeting);
    }
}
TEST(test_parse_participation_element, happy_day_test) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/happy_day.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    Participation participation;
    participation.set_meeting("Meeting_478463");
    participation.set_user("Peter Selie");


    for (TiXmlElement* test_participation = test_root->FirstChildElement("PARTICIPATION"); test_participation != NULL; test_participation = test_participation->NextSiblingElement("PARTICIPATION")) {
        EXPECT_EQ(t_parse_participation_element(test_participation),participation);
    }
}
TEST(test_parse_participation_element, missing_information_test) {
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/missing_information.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    Participation participation;
    participation.set_meeting("fout");
    participation.set_user("fout");


    for (TiXmlElement* test_participation = test_root->FirstChildElement("PARTICIPATION"); test_participation != NULL; test_participation = test_participation->NextSiblingElement("PARTICIPATION")) {
        EXPECT_EQ(t_parse_participation_element(test_participation),participation);
    }
}
TEST(test_meeting_planner, happy_day_test) {
    MeetingPlanner test_planner;
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/happy_day.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* room = test_root->FirstChildElement("ROOM"); room != NULL; room = room->NextSiblingElement("ROOM")) {
        Room new_room = t_parse_room_element(room);
        if (new_room.get_name() != "Fout") {
            test_planner.addRoom(new_room);
        }
        else {
        }

    }

    for (TiXmlElement* meeting = test_root->FirstChildElement("MEETING"); meeting != NULL; meeting = meeting->NextSiblingElement("MEETING")) {
        Meeting new_meeting = t_parse_meeting_element(meeting);
        if (new_meeting.get_room() != "fout") {
            test_planner.addMeeting(new_meeting);
        }
        else {

        }


    }

    for (TiXmlElement* participation = test_root->FirstChildElement("PARTICIPATION"); participation != NULL; participation = participation->NextSiblingElement("PARTICIPATION")) {
        Participation new_participation = t_parse_participation_element(participation);
        if(new_participation.get_meeting() != "fout") {
            test_planner.addParticipation(new_participation);
        }

        else {
        }

    }

    EXPECT_EQ(test_planner.getMeetings().size(), (size_t)1);

}
TEST(test_meeting_planner, meeting_cancelled_test) {
    MeetingPlanner test_planner;
    TiXmlDocument test_doc;
    string test_filename = "../Tests/test_XML_file/meeting_cancelled.xml";
    t_file_error_check(test_filename,test_doc);

    TiXmlElement* test_root = test_doc.FirstChildElement(); // Dit is <system>
    t_if_root_exists(test_root);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* room = test_root->FirstChildElement("ROOM"); room != NULL; room = room->NextSiblingElement("ROOM")) {
        Room new_room = t_parse_room_element(room);
        if (new_room.get_name() != "Fout") {
            test_planner.addRoom(new_room);
        }
        else {
        }

    }

    for (TiXmlElement* meeting = test_root->FirstChildElement("MEETING"); meeting != NULL; meeting = meeting->NextSiblingElement("MEETING")) {
        Meeting new_meeting = t_parse_meeting_element(meeting);
        if (new_meeting.get_room() != "fout") {
            test_planner.addMeeting(new_meeting);
        }
        else {

        }


    }

    for (TiXmlElement* participation = test_root->FirstChildElement("PARTICIPATION"); participation != NULL; participation = participation->NextSiblingElement("PARTICIPATION")) {
        Participation new_participation = t_parse_participation_element(participation);
        if(new_participation.get_meeting() != "fout") {
            test_planner.addParticipation(new_participation);
        }

        else {
        }

    }

    EXPECT_EQ(test_planner.getMeetings().size(), (size_t)1);
}

    // ============================================================================
// CONTRACT VIOLATION TESTS (Death Tests voor Design by Contract)
// ============================================================================

/**
 * Test de precondities van de Room klasse.
 */
TEST(test_contract_violation, roomcontracts) {
    Room test_room;

    // Test REQUIRE: name is not empty
    ASSERT_DEATH({ test_room.set_name(""); }, "Contract violation");

    // Test REQUIRE: identifier is not empty
    ASSERT_DEATH({ test_room.set_identifier(""); }, "Contract violation");

    // Test REQUIRE: capacity is bigger or equal to zero
    // (Opm: aangezien capacity unsigned is, test we hier vooral de macro aanroep)
    // Als je REQUIRE(capacity > 0) gebruikt voor de getter:
    ASSERT_DEATH({ test_room.get_capacity(); }, "Contract violation");
}

/**
 * Test de precondities van de Meeting klasse.
 */
TEST(ContractViolationTest, MeetingContracts) {
    Meeting test_meeting;

    // Test REQUIRE: label is not empty
    ASSERT_DEATH({ test_meeting.set_label(""); }, "Contract violation");

    // Test REQUIRE: identifier is not empty
    ASSERT_DEATH({ test_meeting.set_identifier(""); }, "Contract violation");

    // Test REQUIRE: room is not empty
    ASSERT_DEATH({ test_meeting.set_room(""); }, "Contract violation");

    // Test REQUIRE: date is not empty
    ASSERT_DEATH({ test_meeting.set_date(""); }, "Contract violation");
}

/**
 * Test de precondities van de Participation klasse.
 */
TEST(ContractViolationTest, ParticipationContracts) {
    Participation test_part;

    // Test REQUIRE: user is not empty
    ASSERT_DEATH({ test_part.set_user(""); }, "Contract violation");

    // Test REQUIRE: meeting (ID) is not empty
    ASSERT_DEATH({ test_part.set_meeting(""); }, "Contract violation");
}

/**
 * Test de precondities van de MeetingPlanner klasse.
 */
TEST(ContractViolationTest, MeetingPlannerContracts) {
    MeetingPlanner planner;

    // Test REQUIRE: addRoom (een lege room mag niet toegevoegd worden)
    Room empty_room;
    // De setter van Room blokkeert "" al, maar als je een 'default' room doorgeeft:
    ASSERT_DEATH({ planner.addRoom(empty_room); }, "Contract violation");

    // Test REQUIRE: addMeeting (een meeting zonder ID mag niet toegevoegd worden)
    Meeting empty_meeting;
    ASSERT_DEATH({ planner.addMeeting(empty_meeting); }, "Contract violation");

    // Test REQUIRE: addParticipation
    Participation empty_part;
    ASSERT_DEATH({ planner.addParticipation(empty_part); }, "Contract violation");

    // Test REQUIRE: get_occupied_rooms (indien de lijst leeg is en je REQUIRE(!empty) hebt)
    ASSERT_DEATH({ planner.get_occupied_rooms(); }, "Contract violation");
}

// ============================================================================
// MEETINGPLANNER CONTRACT TESTS (PRE & POST CONDITIONS)
// ============================================================================

/**
 * Test REQUIRE: Precondities (Death Tests)
 */
TEST(MeetingPlannerContractTest, Preconditions) {
    MeetingPlanner planner;

    // REQUIRE: addRoom mag geen lege naam hebben
    Room empty_room;
    ASSERT_DEATH({ planner.addRoom(empty_room); }, "Contract violation");

    // REQUIRE: addMeeting mag geen lege identifier hebben
    Meeting empty_meeting;
    ASSERT_DEATH({ planner.addMeeting(empty_meeting); }, "Contract violation");

    // REQUIRE: addParticipation mag geen lege user hebben
    Participation empty_part;
    ASSERT_DEATH({ planner.addParticipation(empty_part); }, "Contract violation");

    // REQUIRE: get_occupied_rooms mag niet op een lege lijst
    ASSERT_DEATH({ planner.get_occupied_rooms(); }, "Contract violation");

    // REQUIRE: simpleOutput mag niet op een lege planner
    ASSERT_DEATH({ planner.simpleOutput(); }, "Contract violation");
}

/**
 * Test ENSURE: Postcondities (Success Tests)
 */
TEST(MeetingPlannerContractTest, Postconditions) {
    MeetingPlanner planner;

    // 1. Test ENSURE: addRoom (checkt of size met 1 stijgt en object gelijk is)
    Room r;
    r.set_name("Aula");
    r.set_identifier("ID_A");
    r.set_capacity(50);
    EXPECT_NO_THROW(planner.addRoom(r));
    EXPECT_EQ(planner.getRooms().back(), r);

    // 2. Test ENSURE: addMeeting (checkt of meeting is toegevoegd)
    Meeting m; m.set_label("Test");
    m.set_identifier("Meeting_1");
    m.set_room("Aula");
    m.set_date("2026-01-01");
    EXPECT_NO_THROW(planner.addMeeting(m));
    EXPECT_EQ(planner.getMeetings().back(), m);

    // 3. Test ENSURE: addParticipation (checkt of participation is toegevoegd)
    Participation p;
    p.set_user("Jan");
    p.set_meeting("MEETing_1");
    EXPECT_NO_THROW(planner.addParticipation(p));
    EXPECT_EQ(planner.getParticipations().back(), p);

    // 4. Test ENSURE: set_occupied_rooms (checkt of de nieuwe lijst gelijk is)
    vector<string> new_rooms = {"R1", "R2"};
    EXPECT_NO_THROW(planner.set_occupied_rooms(new_rooms));
    EXPECT_EQ(planner.get_occupied_rooms(), new_rooms);
    // 5. Test ENSURE: simpleOutput (checkt of output.txt bestaat)
    // De planner is nu niet meer leeg (bevat een room), dus preconditie is voldaan.

    EXPECT_NO_THROW(planner.simpleOutput());
}


// ============================================================================
// PARSER CLASS TESTS
// ============================================================================

/**
 * Test de basis getters en setters van de Parser
 */
TEST(ParserTest, GetSetFilename) {
    Parser test_parser;

    // Test REQUIRE: mag niet leeg zijn bij set
    ASSERT_DEATH({ test_parser.set_filename(""); }, "Contract violation");

    // Test Happy Day
    test_parser.set_filename("test.xml");
    EXPECT_EQ(test_parser.get_filename(), "test.xml");
}

/**
 * Test de file_error_check functionaliteit van de Parser klasse
 */
TEST(ParserTest, FileErrorCheck) {
    Parser test_parser;
    TiXmlDocument doc;

    // Test REQUIRE: filename mag niet leeg zijn voor de check
    // We moeten een parser object hebben zonder filename (indien mogelijk)
    // of direct de check aanroepen terwijl filename nog niet gezet is.
    ASSERT_DEATH({ test_parser.file_error_check(doc); }, "Contract violation");

    // Test Happy Day: Bestaand bestand
    test_parser.set_filename("../Tests/test_XML_file/happy_day.xml");
    EXPECT_EQ(test_parser.file_error_check(doc), 0);

    // Test Failure: Onbestaand bestand
    test_parser.set_filename("onbestaand_bestand.xml");
    EXPECT_EQ(test_parser.file_error_check(doc), 1);
}

/**
 * Test of de root correct wordt herkend en gemaakt
 */
TEST(ParserTest, RootHandling) {
    Parser test_parser;
    TiXmlDocument doc;

    // Setup: Laad een valide file
    test_parser.set_filename("../Tests/test_XML_file/happy_day.xml");
    test_parser.file_error_check(doc);

    // Test if_root_exists
    TiXmlElement* root = doc.FirstChildElement();
    EXPECT_EQ(test_parser.if_root_exists(root), 0);

    // Test make_root
    TiXmlElement* created_root = test_parser.make_root(doc);
    EXPECT_NE(created_root, nullptr);
    EXPECT_STREQ(created_root->Value(), "SYSTEM"); // Of wat je root tag ook is
}

/**
 * Test de run_trough_Element functie (De kern van de parser)
 */
TEST(ParserTest, RunThroughElement) {
    Parser test_parser;
    MeetingPlanner planner;
    TiXmlDocument doc;

    test_parser.set_filename("../Tests/test_XML_file/happy_day.xml");
    test_parser.file_error_check(doc);
    TiXmlElement* root = test_parser.make_root(doc);

    // Test REQUIRE: Foute element naam (moet ROOM, MEETING of PARTICIPATION zijn)
    ASSERT_DEATH({ test_parser.run_trough_Element("INVALID", root, planner); }, "Contract violation");

    // Test REQUIRE: Root mag niet NULL zijn
    ASSERT_DEATH({ test_parser.run_trough_Element("ROOM", nullptr, planner); }, "Contract violation");

    // Test Happy Day: Verwerk rooms
    test_parser.run_trough_Element("ROOM", root, planner);
    EXPECT_FALSE(planner.getRooms().empty());
}

/**
 * Test de individuele element-parsers (Room, Meeting, Participation)
 */
TEST(ParserTest, ParseElements) {
    Parser test_parser;
    TiXmlDocument doc;
    test_parser.set_filename("../Tests/test_XML_file/happy_day.xml");
    test_parser.file_error_check(doc);
    TiXmlElement* root = test_parser.make_root(doc);

    // Haal een Room element op
    TiXmlElement* room_el = root->FirstChildElement("ROOM");
    if (room_el) {
        Room r = test_parser.parse_room_element(room_el);
        EXPECT_NE(r.get_name(), "Fout");
    }

    // Haal een Meeting element op
    TiXmlElement* meeting_el = root->FirstChildElement("MEETING");
    if (meeting_el) {
        Meeting m = test_parser.parse_meeting_element(meeting_el);
        EXPECT_NE(m.get_identifier(), "fout");
    }

    // Test REQUIRE: mag niet NULL zijn
    ASSERT_DEATH({ test_parser.parse_room_element(nullptr); }, "Contract violation");
    ASSERT_DEATH({ test_parser.parse_meeting_element(nullptr); }, "Contract violation");
    ASSERT_DEATH({ test_parser.parse_participation_element(nullptr); }, "Contract violation");
}
