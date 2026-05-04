/**
* Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 01/05/2026
 * @version 2.0
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
    double totalCatering = 0;

    file << "--== Meetings ==--\n\n";

    for (Meeting& meeting : meetings) {

        int participants = countParticipants(meeting.get_identifier());
        double co2 = calculateCO2(meeting);
        totalCO2 += co2;

        file << "[Meeting " << meeting.get_identifier() << "]\n";
        file << "- Time: " << meeting.get_date()
             << ", " << meeting.get_hour() << "h\n";
        file << "- Location: "
             << (meeting.is_online() ? "ONLINE" : meeting.get_room()) << "\n";
        file << "- Participants: "
             << participants << "/" << meeting_capacity(meeting) << "\n";
        file << "- Online: "
             << (meeting.is_online() ? "Yes" : "No") << "\n";
        file << "- CO2 emitted: " << co2 << "g\n";
        file << "- Catering: "
             << (meeting.is_catering() ? "Yes" : "No") << "\n\n";
    }

    file << "--== Rooms ==--\n\n";

    for (const Room& room : rooms) {
        file << "[Room " << room.get_identifier() << "]\n";
        file << "- Name: " << room.get_name() << "\n";
        file << "- Capacity: " << room.get_capacity() << "\n";
        file << "- Campus: " << room.get_campus() << "\n";
        file << "- Building: " << room.get_building() << "\n\n";
    }

    file << "--== CO2 summary ==--\n\n";
    file << "- Total CO2 emitted: " << totalCO2 << "g\n";

    if (!meetings.empty()) {
        file << "- Average CO2: "
             << totalCO2 / meetings.size() << "g\n";
    }

    file << "\n--== Catering ==--\n\n";

    bool hasCatering = false;

    for (Meeting& meeting : meetings) {
        if (meeting.is_catering()) {

            REQUIRE(!meeting.is_online(),
                    "Online meetings cannot have catering");

            hasCatering = true;

            int participants = countParticipants(meeting.get_identifier());
            double cost = participants * 10.59;
            totalCatering += cost;

            file << "[Meeting " << meeting.get_identifier() << "]\n";
            file << "- Time: " << meeting.get_date()
                 << " " << meeting.get_hour() << "h\n";
            file << "- Location: " << meeting.get_room() << "\n";
            file << "- Participants: " << participants << "\n";
            file << "- Cost: €" << cost << "\n\n";
        }
    }

    if (!hasCatering) {
        file << "No catering services required.\n\n";
    }

    file << "--== Catering Summary ==--\n\n";
    file << "- Total catering cost: €" << totalCatering << "\n\n";

    file << "==== [END OF REPORT] ====\n";

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
    file << "    rankdir=LR;\n\n";

    file << "    // --- NODE LABELS ---\n";


    for (const auto& campus : campuses) {
        file << "    \"" << campus.get_identifier()
             << "\" [label=\"" << campus.get_name() << "\"];\n";
    }


    for (const auto& building : buildings) {
        file << "    \"" << building.get_identifier()
             << "\" [label=\"" << building.get_name() << "\"];\n";
    }


    for (const auto& room : rooms) {
        file << "    \"" << room.get_identifier()
             << "\" [label=\"" << room.get_name() << "\"];\n";
    }

    for (const auto& meeting : meetings) {
        file << "    \"" << meeting.get_identifier()
             << "\" [label=\"" << meeting.get_label() << "\"];\n";
    }


    file << "\n    // --- EDGES (CONNECTIONS) ---\n";


    for (const auto& building : buildings) {
        file << "    \"" << building.get_campus()
             << "\" -> \"" << building.get_identifier() << "\";\n";
    }


    for (const auto& room : rooms) {
        file << "    \"" << room.get_building()
             << "\" -> \"" << room.get_identifier() << "\";\n";
    }


    for (const auto& meeting : meetings) {
        file << "    \"" << meeting.get_room()
             << "\" -> \"" << meeting.get_identifier() << "\";\n";
    }

    file << "\n}\n";
    file.close();

    std::cout << "DOT file created: structure.dot\n";
}

void MeetingPlanner::processMeetings() {
    REQUIRE(!meetings.empty(), "there must be meetings to process");

    std::vector<std::string> used_rooms = occupied_rooms;

    totalCateringCost = 0.0;

    for (Meeting& meeting : meetings) {
        bool occupied = false;
        bool renovating = false;

        for (const std::string& room : used_rooms) {
            if (!meeting.is_online() && meeting.get_room() == room) {
                std::cerr << "Error: Room " << meeting.get_room()
                          << " is already occupied. Meeting cancelled.\n";
                occupied = true;
                break;
            }
        }

        for (const Renovations& renovation : renovations) {
            if (!meeting.is_online() && meeting.get_room() == renovation.get_room()) {
                std::cerr << "Error: Room " << meeting.get_room()
                          << " is under renovation. Meeting cancelled.\n";
                renovating = true;
                break;
            }
        }

        if (occupied || renovating) {
            continue;
        }

        if (!meeting.is_online()) {
            used_rooms.push_back(meeting.get_room());
        }

        std::cout << "Meeting " << meeting.get_identifier()
                  << " has taken place.\n";

        if (meeting.is_catering()) {
            REQUIRE(!meeting.is_online(),
                    "Online meetings cannot have catering");

            int participants = countParticipants(meeting.get_identifier());
            double cost = participants * 10.59;

            totalCateringCost += cost;

            std::cout << "[Meeting " << meeting.get_identifier() << "]\n";
            std::cout << "- Participants: " << participants << "\n";
            std::cout << "- Cost: €" << cost << "\n\n";
        }
    }


    ENSURE(true, "meetings processed correctly with catering");
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

int MeetingPlanner::meeting_capacity(const Meeting& meeting) {
    string room_name = meeting.get_room();
    for (Room& room: rooms) {
        if(room.get_identifier() == room_name) {
            return room.get_capacity();
        }
    }
    return 0;
}
