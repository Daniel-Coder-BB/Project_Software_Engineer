/**
* Korte beschrijving:
 * Deze klasse stelt een meeting voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

#include <iostream>
#include "tinyxml.h"
#include "Classes/Room/Room.h"
#include "Classes/Meeting/Meeting.h"
#include <gtest/gtest.h>
#include <chrono>
#include "Classes/Meeting/Meeting.h"
#include "Classes/Meetingplanner/Meetingplanner.h"
#include "Classes/Participation/Participation.h"

using namespace std;


/*
 *This function parses the room tag of an XML file
 *@param room_element an XML element with the ROOM tag
 *@return new_room a room of the type ROOM with all the details
 */
Room parse_room_element(TiXmlElement* room_element) {
    Room new_room;
    if (room_element->FirstChildElement("NAME")) {
        new_room.set_name(room_element->FirstChildElement("NAME")->GetText());
    }
    if (room_element->FirstChildElement("IDENTIFIER")) {
        new_room.set_identifier(room_element->FirstChildElement("IDENTIFIER")->GetText());
    }
    if (room_element->FirstChildElement("CAPACITY")) {
        // Omzetten van string naar int
        int capacity = std::stoi(room_element->FirstChildElement("CAPACITY")->GetText());
        new_room.set_capacity(capacity);
    }

    return new_room;
}

/*
 *This function parses the meeting tag of an XML file
 *@param meeting_element an XML element with the MEETING tag
 *@return new_meeting a meeting of the type MEETING with all the details
 */
Meeting parse_meeting_element(TiXmlElement* meeting_element) {
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

    return new_meeting;
}


/*
 *This function parses the participation tag of an XML file
 *@param participation_element an XML element with the PARTICIPATION tag
 *@return new_participation a participation of the type PARTICIPATION with all the details
 */
Participation parse_participation_element(TiXmlElement* participation_element) {
    Participation new_participation;
    if (participation_element->FirstChildElement("USER")) {
        new_participation.set_user(participation_element->FirstChildElement("USER")->GetText());
    }
    if (participation_element->FirstChildElement("MEETING")) {
        new_participation.set_meeting(participation_element->FirstChildElement("MEETING")->GetText());
    }


    return new_participation;
}


/*
 *This function checks if an error happens with reading the file
 *@param filename The directory where the file is
 *@param doc a TiXmlDocument wich contains our XML file
 *@return if failed (1) or if no errors(0)
 */
int file_error_check(const string& filename,TiXmlDocument& doc) {

    if (!doc.LoadFile(filename.c_str())) {
        cerr << "Fout bij laden: " << doc.ErrorDesc() << endl;
        return 1;
    }
    return 0;
}


int if_root_exists(TiXmlElement* root) {
    if (root == NULL) {
        cerr << "Geen root element gevonden." << endl;
        return 1;
    }
    return 0;
}



int main(int argc, char **argv) {
    MeetingPlanner planner;
    TiXmlDocument doc;
    string filename = "../XML_files/Room.xml";
    file_error_check(filename,doc);

    TiXmlElement* root = doc.FirstChildElement(); // Dit is <system>
    if_root_exists(root);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* room = root->FirstChildElement("ROOM"); room != NULL; room = room->NextSiblingElement("ROOM")) {
        Room new_room = parse_room_element(room);
        planner.addRoom(new_room);
    }

    for (TiXmlElement* meeting = root->FirstChildElement("MEETING"); meeting != NULL; meeting = meeting->NextSiblingElement("MEETING")) {
        Meeting new_meeting = parse_meeting_element(meeting);
        planner.addMeeting(new_meeting);

    }

    for (TiXmlElement* participation = root->FirstChildElement("PARTICIPATION"); participation != NULL; participation = participation->NextSiblingElement("PARTICIPATION")) {
        Participation new_participation = parse_participation_element(participation);
        planner.addParticipation(new_participation);
    }
    for (auto& room: planner.getParticipations()) {
        room.print();
    }
    doc.Clear();

    // Netjes opruimen [cite: 107]



    return 0;
}

int maaltafel(int x) {
    return x*2;
}
