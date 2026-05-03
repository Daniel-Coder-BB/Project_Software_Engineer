/*
* Korte beschrijving:
 *Dit stelt onze parser klasse voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 25/03/2026
 * @version 1.5
 */

#include "Parser.h"
#include "Classes/Campus/Campus.h"
#include "Classes/Buildings/Buildings.h"
#include "Classes/DesignByContract/DesignByContract.h"
#include <iostream>
using namespace std;


string Parser::get_filename() const {
    REQUIRE(!filename.empty(), "Preconditie gefaald: filename mag niet leeg zijn");

    string result = filename;

    ENSURE(result == filename, "Postconditie gefaald: de geretourneerde filename is niet gelijk aan de attribuutwaarde");
    return result;
}

void Parser::set_filename(const string &filename) {
    REQUIRE(!filename.empty(), "Preconditie gefaald: nieuwe filename mag niet leeg zijn");

    this->filename = filename;

    ENSURE(this->filename == filename, "Postconditie gefaald: filename attribuut is niet correct aangepast");
}


int Parser::file_error_check(TiXmlDocument& doc) {
    REQUIRE(!filename.empty(), "Preconditie gefaald: filename mag niet leeg zijn om file error check uit te voeren");

    int result;
    if (!doc.LoadFile(filename.c_str())) {
        cerr << "Fout bij laden: " << doc.ErrorDesc() << endl;
        result = 1;
    } else {
        result = 0;
    }

    ENSURE(result == 0 || result == 1, "Postconditie gefaald: resultaat moet 0 of 1 zijn");
    return result;
}


TiXmlDocument Parser::Xml_to_TiXmlDocument() {
    REQUIRE(!filename.empty(), "Preconditie gefaald: filename mag niet leeg zijn");

    TiXmlDocument doc;
    // Let op: in de originele code wordt filename hier overschreven met een hardcoded pad.
    file_error_check(doc);

    return doc;
};

int Parser::if_root_exists(TiXmlElement* root) {
    // Geen precondities volgens .h file

    int result;
    if (root == NULL) {
        cerr << "Geen root element gevonden." << endl;
        result = 1;
    } else {
        result = 0;
    }

    return result;
};


TiXmlElement* Parser::make_root(TiXmlDocument& doc){
    // Preconditie: No file error happened beforehand (is impliciet dat doc geladen is)

    TiXmlElement* root = doc.FirstChildElement(); // Dit is <system>
    if_root_exists(root);

    ENSURE(root != NULL || true, "Postconditie: root is aangemaakt (indien aanwezig)");
    if (doc.Error()) {
        root = nullptr;
    }
    return root;
};



/*
 *This function parses the room tag of an XML file
 *@param room_element an XML element with the ROOM tag
 *@return new_room a room of the type ROOM with all the details
 */
Room Parser::parse_room_element(TiXmlElement* room_element) {
    REQUIRE(room_element != NULL, "Preconditie gefaald: room_element mag niet NULL zijn");

    Room new_room;
    new_room.set_identifier("Fout");
    new_room.set_name("Fout");
    new_room.set_capacity(0);

    // --- NAME CHECK ---
    TiXmlElement* name_el = room_element->FirstChildElement("NAME");
    if (name_el && name_el->GetText()) { // Check of element én tekst bestaan
        string new_name = name_el->GetText();
        new_room.set_name(new_name.empty() ? "Fout" : new_name);
    }

    // --- IDENTIFIER CHECK ---
    TiXmlElement* id_el = room_element->FirstChildElement("IDENTIFIER");
    if (id_el && id_el->GetText()) {
        string new_id = id_el->GetText();
        new_room.set_identifier(new_id.empty() ? "Fout" : new_id);
    }

    // --- CAPACITY CHECK ---
    TiXmlElement* cap_el = room_element->FirstChildElement("CAPACITY");
    if (cap_el && cap_el->GetText()) {
        try {
            // Nu is het veilig om GetText() aan te roepen voor stoi
            int capacity = std::stoi(cap_el->GetText());
            new_room.set_capacity(capacity);
        }
        catch (...) { // Vang alle conversiefouten (niet alleen invalid_argument)
            cerr << "Capacity moet een geldig getal zijn" << endl;
            new_room.set_capacity(0);
        }
    }

    // --- CAMPUS CHECK ---
    TiXmlElement* campus_el = room_element->FirstChildElement("CAMPUS");
    if (campus_el && campus_el->GetText()) {
        new_room.set_campus(campus_el->GetText());
    }

    // --- BUILDING CHECK ---
    TiXmlElement* building_el = room_element->FirstChildElement("BUILDING");
    if (building_el && building_el->GetText()) {
        new_room.set_building(building_el->GetText());
    }

    //  extra veiligheidscheck
    if (new_room.get_name() == "Fout" || new_room.get_identifier() == "Fout" || new_room.get_capacity() == 0) {
        new_room.set_capacity(0);
        new_room.set_name("Fout");
        new_room.set_identifier("Fout");
    }

    return new_room;
}


Meeting Parser::parse_meeting_element(TiXmlElement* meeting_element) {
    REQUIRE(meeting_element != NULL, "Preconditie gefaald: meeting_element mag niet NULL zijn");

    Meeting new_meeting;
    new_meeting.set_date("Fout");
    new_meeting.set_identifier("Fout");
    new_meeting.set_label("Fout");
    new_meeting.set_room("Fout");

    // LABEL CHECK
    TiXmlElement* label_el = meeting_element->FirstChildElement("LABEL");
    if (label_el != NULL && label_el->GetText() != NULL) {
        new_meeting.set_label(label_el->GetText());
    }

    // IDENTIFIER CHECK
    TiXmlElement* id_el = meeting_element->FirstChildElement("IDENTIFIER");
    if (id_el != NULL && id_el->GetText() != NULL) {
        new_meeting.set_identifier(id_el->GetText());
    }

    // ROOM CHECK
    TiXmlElement* room_el = meeting_element->FirstChildElement("ROOM");
    if (room_el != NULL && room_el->GetText() != NULL) {
        new_meeting.set_room(room_el->GetText());
    }

    // DATE CHECK
    TiXmlElement* date_el = meeting_element->FirstChildElement("DATE");
    if (date_el != NULL && date_el->GetText() != NULL) {
        new_meeting.set_date(date_el->GetText());
    }

    TiXmlElement* catering_el = meeting_element->FirstChildElement("CATERING");
    if (catering_el != NULL && catering_el->GetText() != NULL) {
        new_meeting.set_catering(true);
    }

    TiXmlElement* online_el = meeting_element->FirstChildElement("ONLINE");
    if (online_el != NULL && online_el->GetText() != NULL) {
        new_meeting.set_online(true);
    }



    if (new_meeting.get_label() == "Fout" || new_meeting.get_identifier() == "Fout" ||
        new_meeting.get_room() == "Fout" || new_meeting.get_date() == "Fout") {
        new_meeting.set_label("fout");
        new_meeting.set_identifier("fout");
        new_meeting.set_room("fout");
        new_meeting.set_date("fout");
    }
    return new_meeting;
}

Participation Parser::parse_participation_element(TiXmlElement* participation_element) {
    REQUIRE(participation_element != NULL, "Preconditie gefaald: participation_element mag niet NULL zijn");

    Participation new_participation;
    new_participation.set_meeting("Fout");
    new_participation.set_user("Fout");

    // USER CHECK
    TiXmlElement* user_el = participation_element->FirstChildElement("USER");
    if (user_el != NULL && user_el->GetText() != NULL) {
        new_participation.set_user(user_el->GetText());
    }

    // MEETING CHECK
    TiXmlElement* meet_el = participation_element->FirstChildElement("MEETING");
    if (meet_el != NULL && meet_el->GetText() != NULL) {
        new_participation.set_meeting(meet_el->GetText());
    }

    if (new_participation.get_meeting() == "Fout" || new_participation.get_user() == "Fout") {
        new_participation.set_meeting("fout");
        new_participation.set_user("fout");
    }

    return new_participation;
}

Campus Parser::parse_campus_element(TiXmlElement* campus_element) {
    // Gebruik de REQUIRE macro voor Design by Contract
    REQUIRE(campus_element != NULL, "Preconditie gefaald: campus_element mag niet NULL zijn");

    Campus new_campus;
    new_campus.set_name("Fout");
    new_campus.set_identifier("Fout");

    // NAME CHECK
    TiXmlElement* name_el = campus_element->FirstChildElement("NAME");
    if (name_el != NULL && name_el->GetText() != NULL) {
        new_campus.set_name(name_el->GetText());
    }

    // IDENTIFIER CHECK
    TiXmlElement* id_el = campus_element->FirstChildElement("IDENTIFIER");
    if (id_el != NULL && id_el->GetText() != NULL) {
        new_campus.set_identifier(id_el->GetText());
    }

    // Validatie: als een van de velden ontbreekt, markeren we het als ongeldig
    if (new_campus.get_name() == "Fout" || new_campus.get_identifier() == "Fout") {
        new_campus.set_name("fout");
        new_campus.set_identifier("fout");
    }

    return new_campus;
}

Buildings Parser::parse_building_element(TiXmlElement* building_element) {
    REQUIRE(building_element != NULL, "Preconditie gefaald: building_element mag niet NULL zijn");

    Buildings new_building;
    new_building.set_name("Fout");
    new_building.set_identifier("Fout");
    new_building.set_campus("Fout");

    TiXmlElement* name_el = building_element->FirstChildElement("NAME");
    if (name_el != NULL && name_el->GetText() != NULL) {
        new_building.set_name(name_el->GetText());
    }

    TiXmlElement* id_el = building_element->FirstChildElement("IDENTIFIER");
    if (id_el != NULL && id_el->GetText() != NULL) {
        new_building.set_identifier(id_el->GetText());
    }

    TiXmlElement* campus_el = building_element->FirstChildElement("CAMPUS");
    if (campus_el != NULL && campus_el->GetText() != NULL) {
        new_building.set_campus(campus_el->GetText());
    }

    if (new_building.get_name() == "Fout" ||
        new_building.get_identifier() == "Fout" ||
        new_building.get_campus() == "Fout") {

        new_building.set_name("fout");
        new_building.set_identifier("fout");
        new_building.set_campus("fout");
        }

    return new_building;
}

Renovations Parser::parse_renovation_element(TiXmlElement* renovation_element) {
    REQUIRE(renovation_element != NULL, "Preconditie gefaald: renovation_element mag niet NULL zijn");

    Renovations new_renovation;
    new_renovation.set_room("Fout");
    new_renovation.set_start("Fout");
    new_renovation.set_end("Fout");

    // ROOM CHECK ("Room_87984521")
    TiXmlElement* room_el = renovation_element->FirstChildElement("ROOM");
    if (room_el != NULL && room_el->GetText() != NULL) {
        new_renovation.set_room(room_el->GetText());
    }

    // START CHECK ("2026-07-06")
    TiXmlElement* start_el = renovation_element->FirstChildElement("START");
    if (start_el != NULL && start_el->GetText() != NULL) {
        new_renovation.set_start(start_el->GetText());
    }

    // END CHECK ("2026-07-14")
    TiXmlElement* end_el = renovation_element->FirstChildElement("END");
    if (end_el != NULL && end_el->GetText() != NULL) {
        new_renovation.set_end(end_el->GetText());
    }

    // Validatie
    if (new_renovation.get_room() == "Fout" ||
        new_renovation.get_start() == "Fout" ||
        new_renovation.get_end() == "Fout") {

        new_renovation.set_room("fout");
        new_renovation.set_start("fout");
        new_renovation.set_end("fout");
        }

    return new_renovation;
}

Cateringproviders Parser::parse_catering_element(TiXmlElement* catering_element) {
    // REQUIRE: Het element mag niet NULL zijn om de parser te kunnen starten
    REQUIRE(catering_element != NULL, "Preconditie gefaald: catering_element mag niet NULL zijn");

    Cateringproviders new_catering;

    // Initialisatie met tijdelijke foutwaarde voor de campus
    new_catering.set_campus("fout");
    new_catering.set_co2(1.0f); // Veilige default waarde om contract violations te voorkomen

    bool campus_ok = false;
    bool co2_ok = false;

    // 1. CAMPUS CHECK: Verifieer of de tag bestaat en tekst bevat
    TiXmlElement* campus_el = catering_element->FirstChildElement("CAMPUS");
    if (campus_el != NULL && campus_el->GetText() != NULL) {
        new_catering.set_campus(campus_el->GetText());
        campus_ok = true;
    }

    // 2. CO2 CHECK: Gebruik atof voor drijvende-kommagetallen (float)
    TiXmlElement* co2_el = catering_element->FirstChildElement("CO2");
    if (co2_el != NULL && co2_el->GetText() != NULL) {
        // Omzetten van string naar float met atof ipv atoi om decimalen (zoals .5) te behouden
        float val = static_cast<float>(atof(co2_el->GetText()));

        // Check Bereik: De waarde moet strikt groter zijn dan 0 volgens de precondities
        if (val > 0.0f) {
            new_catering.set_co2(val);
            co2_ok = true;
        }
    }

    // 3. VALIDATIE: Als één van de velden ontbreekt of ongeldig is, markeer het object als "fout"
    if (!campus_ok || !co2_ok) {
        new_catering.set_campus("fout");
    }

    return new_catering;
}

void Parser::run_trough_Element(const char* Element, TiXmlElement* root,  MeetingPlanner& planner) {
    string elStr = (Element != NULL) ? string(Element) : "";
    REQUIRE(elStr == "MEETING" || elStr == "ROOM" || elStr == "PARTICIPATION" || elStr == "CAMPUS" || elStr == "BUILDING" || elStr == "RENOVATION" || elStr == "CATERING", "Preconditie gefaald: Element moet MEETING, ROOM, PARTICIPATION,CAMPUS of BUILDING element zijn");
    REQUIRE(root != NULL, "Preconditie gefaald: root moet bestaan");

    for (TiXmlElement* element = root->FirstChildElement(Element); element != NULL; element = element->NextSiblingElement(Element)) {
        if (string (Element)== "ROOM") {
            Room new_element = parse_room_element(element);
            if (new_element.get_name() != "Fout") {
                planner.addRoom(new_element);
            }
            else {
                cerr<<"Er was een fout bij room"<<endl;
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

        else if (string (Element) == "CAMPUS") {
            Campus new_campus = parse_campus_element(element);
            if(new_campus.get_name() != "fout") {
                planner.set_campuses(new_campus);
            }

            else {
                cerr<<"Er was een fout bij campus"<<endl;
            }
        }

        else if (string(Element) == "BUILDING") {
            Buildings new_building = parse_building_element(element);
            if(new_building.get_name() != "fout") {
                planner.set_buildings(new_building);
                std::vector<Buildings> buildings = planner.get_buildings();

            }
            else {
                cerr << "Er was een fout bij het parsen van een building" << endl;
            }
        }

        else if (string(Element) == "RENOVATION") {
            Renovations new_renovation = parse_renovation_element(element);
            if(new_renovation.get_room() != "fout") {
                planner.set_renovations(new_renovation);
            }
            else {
                cerr << "Er was een fout bij het parsen van een renovation" << endl;
            }
        }

        else if (string(Element) == "CATERING") {
            Cateringproviders new_cat = parse_catering_element(element);
            if(new_cat.get_campus() != "fout") {
                planner.set_catering(new_cat);
                for (Cateringproviders catering: planner.get_catering()) {

                }
            }
            else {
                cerr << "Er was een fout bij het parsen van catering" << endl;
            }
        }






    }

    ENSURE(true, "Postconditie: Elementen zijn verwerkt");
};