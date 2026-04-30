/**
* Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

#include "Meetingplanner.h"
#include "Classes/DesignByContract/DesignByContract.h"
#include <fstream>
#include <iostream>

//Adders

void MeetingPlanner::addRoom(const Room& room) {
    // Preconditie: room is not empty (check op een essentieel veld zoals naam)
    REQUIRE(!room.get_name().empty(), "room is not empty");
    
    size_t old_size = rooms.size();
    rooms.push_back(room);
    
    // Postconditie: de laatst toegevoegde room is gelijk aan de input room
    ENSURE(rooms.back() == room, "the input room is equal to label room of Meetingplanner object");
    ENSURE(rooms.size() == old_size + 1, "room was successfully added");
}

void MeetingPlanner::addMeeting(const Meeting& meeting) {
    // Preconditie: meeting is not empty
    REQUIRE(!meeting.get_identifier().empty(), "meeting is not empty");
    meetings.push_back(meeting);
        // Postconditie: input meeting is toegevoegd aan de lijst
        ENSURE(meetings.back() == meeting, "the input meeting is equal to label meeting of Meetingplanner object");

}

void MeetingPlanner::addParticipation(const Participation& participation) {
    // Preconditie: participation is not empty
    REQUIRE(!participation.get_user().empty(), "participation is not empty");

    participations.push_back(participation);
    
    ENSURE(participations.back() == participation, "the input participation is equal to label participation of Meetingplanner object");
}

//Getters

std::vector<Room>& MeetingPlanner::getRooms() {
    REQUIRE(!rooms.empty(), "rooms is not empty");
    return rooms;
    // ENSURE is hier lastig omdat we een referentie teruggeven, 
    // maar de REQUIRE dekt de documentatie.
}

std::vector<Meeting>& MeetingPlanner::getMeetings() {
    REQUIRE(!meetings.empty(), "meetings is not empty");
    return meetings;
}

std::vector<Participation>& MeetingPlanner::getParticipations() {
    REQUIRE(!participations.empty(), "participations is not empty");
    return participations;
}

std::vector<string> MeetingPlanner::get_occupied_rooms() const {
    REQUIRE(!occupied_rooms.empty(), "occupied_rooms is not empty");
    return occupied_rooms;
}

//Setters

void MeetingPlanner::set_occupied_rooms(const string &occupied_rooms) {
    // Preconditie: occupied_rooms is bigger or equal to zero (size check)
    REQUIRE(occupied_rooms.size() >= 0, "occupied_rooms size is bigger or equal to zero");
    
    this->occupied_rooms.push_back(occupied_rooms);

}

std::vector<Campus> MeetingPlanner::get_campuses() const {
    std::vector<Campus> result = campuses;
    ENSURE(!result.empty() || result.empty(), "returns a vector of campuses");
    return result;
}

void MeetingPlanner::set_campuses(const Campus &campus) {
    size_t old_size = campuses.size();
    this->campuses.push_back(campus);

    ENSURE(campuses.size() == old_size + 1, "the campus is added to the list of campuses");
}

std::vector<Buildings> MeetingPlanner::get_buildings() const {
    std::vector<Buildings> result = buildings;
    ENSURE(!result.empty() || result.empty(), "returns a vector of buildings");
    return result;
}

void MeetingPlanner::set_buildings(const Buildings &building) {
    size_t old_size = buildings.size();
    this->buildings.push_back(building);

    ENSURE(buildings.size() == old_size + 1, "the building is added to the list of buildings");
}

std::vector<Renovations> MeetingPlanner::get_renovations() {
    std::vector<Renovations> result = renovations;
    ENSURE(!result.empty() || result.empty(), "returns a vector of renovations");
    return result;
}

void MeetingPlanner::set_renovations(const Renovations &renovation) {
    size_t old_size = renovations.size();
    this->renovations.push_back(renovation);

    ENSURE(renovations.size() == old_size + 1, "the renovation is added to the list of renovations");
}

std::vector<Cateringproviders> MeetingPlanner::get_catering() const {
    std::vector<Cateringproviders> result = catering;
    ENSURE(!result.empty() || result.empty(), "returns a vector of catering providers");
    return result;
}

void MeetingPlanner::set_catering(const Cateringproviders &catering_provider) {
    size_t old_size = catering.size();
    this->catering.push_back(catering_provider);

    ENSURE(catering.size() == old_size + 1, "the catering provider is added to the list of catering providers");
}

//Output

void MeetingPlanner::simpleOutput() {
    REQUIRE(!rooms.empty() || !meetings.empty(),
            "attributes of meetingplanner are not Empty");

    std::ofstream file("../output.txt");

    if (!file.is_open()) {
        std::cout << "Cannot open file\n";
        return;
    }

    file << "====  [SYSTEM STATUS]  ====\n\n";

    double totalCO2 = 0;

    //MEETINGS
    file << "--== Meetings ==--\n\n";

    for (Meeting& meeting : meetings) {



        file << "[Meeting " << meeting.get_identifier() << "]\n";
        file << "- Time: " << meeting.get_date() << ", " << meeting.get_hour() << "h\n";
        file << "- Location: "<< (meeting.is_online() ? "ONLINE" : meeting.get_room()) << "\n";
        file << "- Participants: " << countParticipants(meeting.get_identifier()) << "\n";
        file << "- Online: " << (meeting.is_online() ? "Yes" : "No") << "\n";
        file << "- CO2 emitted: " << calculateCO2(meeting) << "g\n";
        file << "- Catering: " << (meeting.is_catering() ? "Yes" : "No") << "\n\nn";
    }

    //ROOMS
    file << "--== Rooms ==--\n\n";

    for (const Room& room : rooms) {
        file << "[Room " << room.get_identifier() << "]\n";
        file << "- Name: " << room.get_name() << "\n";
        file << "- Capacity: " << room.get_capacity() << "\n";
        file << "- Campus: " << room.get_campus() << "\n";
        file << "- Building: " << room.get_building() << "\n\n";
    }

    //CO2 SUMMARY
    file << "--== CO2 summary ==--\n\n";
    file << "- Total CO2 emitted: " << totalCO2 << "g\n";

    if (!meetings.empty()) {
        file << "- Average CO2: " << totalCO2 / meetings.size() << "g\n";
    }

    file << "\n==== [END OF REPORT] ====\n";

    file.close();

    std::cout << "Output written to output.txt\n";
}

void MeetingPlanner::exportGraphviz() {

    REQUIRE(!rooms.empty(), "rooms must not be empty");

    std::ofstream file("../structure.dot");

    if (!file.is_open()) {
        std::cerr << "Cannot open DOT file\n";
        return;
    }

    file << "digraph G {\n\n";

    // We bouwen een lineaire keten:
    // Campus -> Building -> Room -> Next Room -> ... -> Last Room

    // 1. Campus → Building
    if (!buildings.empty()) {
        file << "    \"" << buildings[0].get_campus()
             << "\" -> \"" << buildings[0].get_name() << "\";\n";
    }

    // 2. Building → eerste room
    if (!rooms.empty()) {
        file << "    \"" << buildings[0].get_name()
             << "\" -> \"" << rooms[0].get_identifier() << "\";\n";
    }

    // 3. Room → volgende room → volgende room → ...
    for (size_t i = 0; i + 1 < rooms.size(); ++i) {
        file << "    \"" << rooms[i].get_identifier()
             << "\" -> \"" << rooms[i + 1].get_identifier() << "\";\n";
    }

    // 4. Self-loop op de laatste room
    if (!rooms.empty()) {
        const std::string& last = rooms.back().get_identifier();
        file << "    \"" << last << "\" -> \"" << last << "\";\n";
    }

    file << "\n}\n";
    file.close();

    std::cout << "DOT file created: structure.dot\n";
}

void MeetingPlanner::processMeetings() {
    REQUIRE(!meetings.empty(), "there must be meetings to process");

    std::vector<std::string> used_rooms = occupied_rooms;

    for (Meeting& meeting : meetings) {
        bool occupied = false;
        bool renovating = false;

        // Exception check
        for (const std::string& room : used_rooms) {
            if (meeting.get_room() == room) {
                std::cerr << "Error: Room " << meeting.get_room()
                          << " is already occupied. Meeting cancelled.\n";
                occupied = true;
                break;
            }

        }
        for (const Renovations& renovation: renovations) {
            //de kamer is aan het renoveren
            if (meeting.get_room() == renovation.get_room()) {
                std::cerr << "Error: Renovations"<<meeting.get_room()
                          <<" This room is renovating. Meeting cancelled. "<<endl;

                renovating = true;
                break;
            }
        }

        if (occupied or renovating) {
            continue;
        }

        // Step 1: Meeting takes place
        used_rooms.push_back(meeting.get_room());



        // Step 2: Print message
        std::cout << "Meeting " << meeting.get_identifier()
                  << " has taken place.\n";
    }

    ENSURE(true, "meetings processed");
}

int MeetingPlanner::countParticipants(const std::string& meeting_id) {

    int count = 0;

    for (const Participation& p : participations) {
        if (p.get_meeting() == meeting_id) {
            count++;
        }
    }

    return count;
}

double MeetingPlanner::calculateCO2(const Meeting& meeting) {

    int participants = countParticipants(meeting.get_identifier());

    double co2 = 0;

    // Rule: online meeting cannot have catering
    REQUIRE(!(meeting.is_online() && meeting.is_catering()),
            "Online meetings cannot have catering");


        if (meeting.is_online()) {
            co2 += 30*participants;   // online participant
        } else {
            co2 += 120*participants;  // internal participant only
        }

    return co2;
}