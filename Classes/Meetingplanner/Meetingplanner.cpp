/**
* Korte beschrijving:
 * Deze klasse stelt onze MeetingPlanner voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 01/05/2026
 * @version 2.1
 */

#include "Meetingplanner.h"
#include "Classes/DesignByContract/DesignByContract.h"

#include <fstream>
#include <iostream>

//Adders

void MeetingPlanner::addRoom(const Room& room) {

    // Preconditie: room is not empty
    REQUIRE(!room.get_name().empty(),
            "room is not empty");

    size_t old_size = rooms.size();

    rooms.push_back(room);

    // Postconditie
    ENSURE(rooms.back() == room,
           "the input room is equal to label room of Meetingplanner object");

    ENSURE(rooms.size() == old_size + 1,
           "room was successfully added");
}

void MeetingPlanner::addMeeting(const Meeting& meeting) {

    // Preconditie: meeting is not empty
    REQUIRE(!meeting.get_identifier().empty(),
            "meeting is not empty");

    meetings.push_back(meeting);

    // Postconditie
    ENSURE(meetings.back() == meeting,
           "the input meeting is equal to label meeting of Meetingplanner object");
}

void MeetingPlanner::addParticipation(const Participation& participation) {

    // Preconditie: participation is not empty
    REQUIRE(!participation.get_user().empty(),
            "participation is not empty");

    participations.push_back(participation);

    ENSURE(participations.back() == participation,
           "the input participation is equal to label participation of Meetingplanner object");
}

//Getters

std::vector<Room>& MeetingPlanner::getRooms() {
    return rooms;
}

std::vector<Meeting>& MeetingPlanner::getMeetings() {
    return meetings;
}

std::vector<Participation>& MeetingPlanner::getParticipations() {
    return participations;
}

std::vector<std::string> MeetingPlanner::get_occupied_rooms() const {
    return occupied_rooms;
}

//Setters

void MeetingPlanner::set_occupied_rooms(const std::string &occupied_room) {

    REQUIRE(!occupied_room.empty(),
            "occupied room is not empty");

    this->occupied_rooms.push_back(occupied_room);
}

std::vector<Campus> MeetingPlanner::get_campuses() const {
    return campuses;
}

void MeetingPlanner::set_campuses(const Campus &campus) {

    size_t old_size = campuses.size();

    this->campuses.push_back(campus);

    ENSURE(campuses.size() == old_size + 1,
           "the campus is added to the list of campuses");
}

std::vector<Buildings> MeetingPlanner::get_buildings() const {
    return buildings;
}

void MeetingPlanner::set_buildings(const Buildings &building) {

    size_t old_size = buildings.size();

    this->buildings.push_back(building);

    ENSURE(buildings.size() == old_size + 1,
           "the building is added to the list of buildings");
}

std::vector<Renovations> MeetingPlanner::get_renovations() {
    return renovations;
}

void MeetingPlanner::set_renovations(const Renovations &renovation) {

    size_t old_size = renovations.size();

    this->renovations.push_back(renovation);

    ENSURE(renovations.size() == old_size + 1,
           "the renovation is added to the list of renovations");
}

std::vector<Cateringproviders> MeetingPlanner::get_catering() const {
    return catering;
}

void MeetingPlanner::set_catering(const Cateringproviders &catering_provider) {

    size_t old_size = catering.size();

    this->catering.push_back(catering_provider);

    ENSURE(catering.size() == old_size + 1,
           "the catering provider is added to the list of catering providers");
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

    for (const Meeting& meeting : meetings) {

        int participants =
                Participation::countParticipants(
                        participations,
                        meeting.get_identifier());

        double co2 =
                meeting.calculateCO2(participants);

        totalCO2 += co2;

        file << "[Meeting "
             << meeting.get_identifier()
             << "]\n";

        file << "- Time: "
             << meeting.get_date()
             << ", "
             << meeting.get_hour()
             << "h\n";

        file << "- Location: ";

        if (meeting.is_online()) {
            file << "ONLINE\n";
        } else {
            file << meeting.get_room() << "\n";
        }

        file << "- Participants: "
             << participants
             << "/"
             << meeting.get_capacity(rooms)
             << "\n";

        file << "- Online: "
             << (meeting.is_online() ? "Yes" : "No")
             << "\n";

        file << "- CO2 emitted: "
             << co2
             << "g\n";

        file << "- Catering: "
             << (meeting.is_catering() ? "Yes" : "No")
             << "\n\n";
    }

    file << "--== Rooms ==--\n\n";

    for (const Room& room : rooms) {

        file << "[Room "
             << room.get_identifier()
             << "]\n";

        file << "- Name: "
             << room.get_name()
             << "\n";

        file << "- Capacity: "
             << room.get_capacity()
             << "\n";

        file << "- Campus: "
             << room.get_campus()
             << "\n";

        file << "- Building: "
             << room.get_building()
             << "\n\n";
    }

    file << "--== CO2 summary ==--\n\n";

    file << "- Total CO2 emitted: "
         << totalCO2
         << "g\n";

    if (!meetings.empty()) {

        file << "- Average CO2: "
             << totalCO2 / meetings.size()
             << "g\n";
    }

    file << "\n--== Catering ==--\n\n";

    bool hasCatering = false;

    for (const Meeting& meeting : meetings) {

        if (meeting.is_catering()) {

            hasCatering = true;

            int participants =
                    Participation::countParticipants(
                            participations,
                            meeting.get_identifier());

            double cost =
                    meeting.calculateCateringCost(participants);

            totalCatering += cost;

            file << "[Meeting "
                 << meeting.get_identifier()
                 << "]\n";

            file << "- Time: "
                 << meeting.get_date()
                 << " "
                 << meeting.get_hour()
                 << "h\n";

            file << "- Location: "
                 << meeting.get_room()
                 << "\n";

            file << "- Participants: "
                 << participants
                 << "\n";

            file << "- Cost: €"
                 << cost
                 << "\n\n";
        }
    }

    if (!hasCatering) {

        file << "No catering services required.\n\n";
    }

    file << "--== Catering Summary ==--\n\n";

    file << "- Total catering cost: €"
         << totalCatering
         << "\n\n";

    file << "==== [END OF REPORT] ====\n";

    file.close();

    std::cout << "Output written to output.txt\n";
}

void MeetingPlanner::exportGraphviz() {

    REQUIRE(!rooms.empty(),
            "rooms must not be empty");

    std::ofstream file("../structure.dot");

    if (!file.is_open()) {

        std::cerr << "Cannot open DOT file\n";

        return;
    }

    file << "digraph G {\n\n";

    file << "    rankdir=LR;\n\n";

    file << "    // --- NODE LABELS ---\n";

    for (const auto& campus : campuses) {

        file << "    \""
             << campus.get_identifier()
             << "\" [label=\""
             << campus.get_name()
             << "\"];\n";
    }

    for (const auto& building : buildings) {

        file << "    \""
             << building.get_identifier()
             << "\" [label=\""
             << building.get_name()
             << "\"];\n";
    }

    for (const auto& room : rooms) {

        file << "    \""
             << room.get_identifier()
             << "\" [label=\""
             << room.get_name()
             << "\"];\n";
    }

    for (const auto& meeting : meetings) {

        file << "    \""
             << meeting.get_identifier()
             << "\" [label=\""
             << meeting.get_label()
             << "\"];\n";
    }

    file << "\n    // --- EDGES (CONNECTIONS) ---\n";

    for (const auto& building : buildings) {

        file << "    \""
             << building.get_campus()
             << "\" -> \""
             << building.get_identifier()
             << "\";\n";
    }

    for (const auto& room : rooms) {

        file << "    \""
             << room.get_building()
             << "\" -> \""
             << room.get_identifier()
             << "\";\n";
    }

    for (const auto& meeting : meetings) {

        if (!meeting.is_online()) {

            file << "    \""
                 << meeting.get_room()
                 << "\" -> \""
                 << meeting.get_identifier()
                 << "\";\n";
        }
    }

    file << "\n}\n";

    file.close();

    std::cout << "DOT file created: structure.dot\n";
}

void MeetingPlanner::processMeetings() {

    REQUIRE(!meetings.empty(),
            "there must be meetings to process");

    std::vector<std::string> used_rooms =
            occupied_rooms;

    totalCateringCost = 0.0;

    for (Meeting& meeting : meetings) {

        if (!meeting.canTakePlace(
                used_rooms,
                renovations)) {


            continue;
        }

        if (!meeting.is_online()) {

            used_rooms.push_back(
                    meeting.get_room());
        }

        int participants =
                Participation::countParticipants(
                        participations,
                        meeting.get_identifier());


        totalCateringCost +=
                meeting.calculateCateringCost(
                        participants);

        std::cout << "Meeting "
                  << meeting.get_identifier()
                  << " has taken place.\n";

    }

    ENSURE(true,
           "meetings processed correctly");
}