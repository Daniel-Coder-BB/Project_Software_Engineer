#include <iostream>
#include "tinyxml.h"
#include "Classes/Room/Room.h"
#include "Classes/Meeting/Meeting.h"
#include <gtest/gtest.h>
#include <chrono>

#include "Classes/Participation/Participation.h"

using namespace std;

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
        new_meeting.set_room(meeting_element->FirstChildElement("DATE")->GetText());
    }

    return new_meeting;
}


Participation parse_participation_element(TiXmlElement* participation_element) {
    Participation new_participation;
    if (participation_element->FirstChildElement("LABEL")) {
        new_participation.set_user(participation_element->FirstChildElement("LABEL")->GetText());
    }
    if (participation_element->FirstChildElement("IDENTIFIER")) {
        new_participation.set_meeting(participation_element->FirstChildElement("IDENTIFIER")->GetText());
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
    TiXmlDocument doc;
    string filename = "../XML_files/Room.xml";
    file_error_check(filename,doc);

    TiXmlElement* root = doc.FirstChildElement(); // Dit is <system>
    if_root_exists(root);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* room = root->FirstChildElement("ROOM"); room != NULL; room = room->NextSiblingElement("ROOM")) {
        Room new_room = parse_room_element(room);
        new_room.print();
    }

    for (TiXmlElement* meeting = root->FirstChildElement("MEETING"); meeting != NULL; meeting = meeting->NextSiblingElement("MEETING")) {
        Meeting new_meeting = parse_meeting_element(meeting);
        new_meeting.print();
    }

    for (TiXmlElement* participation = root->FirstChildElement("MEETING"); participation != NULL; participation = participation->NextSiblingElement("MEETING")) {
        Participation new_participation = parse_participation_element(participation);
        new_participation.print();
    }

    doc.Clear();

    // Netjes opruimen [cite: 107]



    return 0;
}

int maaltafel(int x) {
    return x*2;
}
TEST(maaltafelTest, Happydaytest) {
    int test_number = 5;
    EXPECT_EQ(maaltafel(test_number),10);
}