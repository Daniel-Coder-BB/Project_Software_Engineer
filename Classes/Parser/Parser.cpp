/*
* Korte beschrijving:
 *Dit stelt onze parser klasse voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 25/03/2026
 * @version 1.5
 */

#include "Parser.h"
#include <iostream>
using namespace std;


string Parser::get_filename() const {

    return filename;
}

void Parser::set_filename(const string &filename) {
    this->filename = filename;
}


int Parser::file_error_check(TiXmlDocument& doc) {
    if (!doc.LoadFile(filename.c_str())) {
        cerr << "Fout bij laden: " << doc.ErrorDesc() << endl;
        return 1;
    }
    return 0;
}


TiXmlDocument Parser::Xml_to_TiXmlDocument() {
    TiXmlDocument doc;
    string filename = "../XML_files/Room.xml";
    file_error_check(doc);

    return doc;
};
int Parser::if_root_exists(TiXmlElement* root) {
    if (root == NULL) {
        cerr << "Geen root element gevonden." << endl;
        return 1;
    }
    return 0;
};


TiXmlElement* Parser::make_root(TiXmlDocument& doc){
    TiXmlElement* root = doc.FirstChildElement(); // Dit is <system>
    if_root_exists(root);

    return root;
};



/*
 *This function parses the room tag of an XML file
 *@param room_element an XML element with the ROOM tag
 *@return new_room a room of the type ROOM with all the details
 */
Room Parser::parse_room_element(TiXmlElement* room_element) {
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
Meeting Parser::parse_meeting_element(TiXmlElement* meeting_element) {
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
Participation Parser::parse_participation_element(TiXmlElement* participation_element) {
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

void Parser::run_trough_Element(const char* Element, TiXmlElement* root,  MeetingPlanner& planner) {
    for (TiXmlElement* element = root->FirstChildElement(Element); element != NULL; element = element->NextSiblingElement(Element)) {
        if (string (Element)== "ROOM") {
            Room new_element = parse_room_element(element);
            if (new_element.get_name() != "Fout") {
                planner.addRoom(new_element);
            }
            else {
                cerr<<"Er was een fout bij element"<<endl;
            }
        }
        else if (string (Element) == "MEETING") {
            Meeting new_meeting = parse_meeting_element(element);
            if (new_meeting.get_room() != "fout") {
                planner.addMeeting(new_meeting);
            }
            else {
                cerr<<"Er was een fout bij meeting"<<endl;
            }

        }
        else if (string (Element) == "PARTICIPATION") {
            Participation new_participation = parse_participation_element(element);
            if(new_participation.get_meeting() != "fout") {
                planner.addParticipation(new_participation);
            }

            else {
                cerr<<"Er was een fout bij participation"<<endl;
            }
        }
    }
};

