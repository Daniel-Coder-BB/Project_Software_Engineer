//
// Created by danny on 10-Mar-26.
//

#include <gtest/gtest.h>
#include <iostream>
#include "tinyxml.h"
#include "Classes/Room/Room.h"
#include "Classes/Meeting/Meeting.h"
#include <gtest/gtest.h>
#include <chrono>
#include <pstl/execution_defs.h>
#include "Classes/Meeting/Meeting.h"
#include "Classes/Participation/Participation.h"
#include <Classes/Meetingplanner/Meetingplanner.h>

using namespace std;


/*
 *This function parses the room tag of an XML file
 *@param room_element an XML element with the ROOM tag
 *@return new_room a room of the type ROOM with all the details
 */
Room t_parse_room_element(TiXmlElement* room_element) {
    Room new_room;
    if (room_element->FirstChildElement("NAME")) {
        new_room.set_name(room_element->FirstChildElement("NAME")->GetText());
    }
    if (room_element->FirstChildElement("IDENTIFIER")) {
        new_room.set_identifier(room_element->FirstChildElement("IDENTIFIER")->GetText());
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
    if (new_room.get_name() == "" or new_room.get_identifier()=="" or new_room.get_capacity() == 0) {
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
    if (new_meeting.get_label() == "" or new_meeting.get_identifier()=="" or new_meeting.get_room()=="" or new_meeting.get_date()=="") {
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
    if (participation_element->FirstChildElement("USER")) {
        new_participation.set_user(participation_element->FirstChildElement("USER")->GetText());
    }
    if (participation_element->FirstChildElement("MEETING")) {
        new_participation.set_meeting(participation_element->FirstChildElement("MEETING")->GetText());
    }
    if (new_participation.get_meeting() == "" or new_participation.get_user()=="") {
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