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

// --- Adders ---

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
    
    bool cancel_meeting = false;

    for (const string& occupied_room : occupied_rooms) {
        if (meeting.get_room() == occupied_room) {
            std::cerr << "This room is occupied. Meeting cancelled" << std::endl;
            conflicting_meetings.push_back(meeting);
            cancel_meeting = true;
        }
    }

    if (!cancel_meeting) {
        meetings.push_back(meeting);
        occupied_rooms.push_back(meeting.get_room());
        
        // Postconditie: input meeting is toegevoegd aan de lijst
        ENSURE(meetings.back() == meeting, "the input meeting is equal to label meeting of Meetingplanner object");
    }
}

void MeetingPlanner::addParticipation(const Participation& participation) {
    // Preconditie: participation is not empty
    REQUIRE(!participation.get_user().empty(), "participation is not empty");

    participations.push_back(participation);
    
    ENSURE(participations.back() == participation, "the input participation is equal to label participation of Meetingplanner object");
}

// --- Getters ---

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

// --- Setters ---

void MeetingPlanner::set_occupied_rooms(const std::vector<string> &occupied_rooms) {
    // Preconditie: occupied_rooms is bigger or equal to zero (size check)
    REQUIRE(occupied_rooms.size() >= 0, "occupied_rooms size is bigger or equal to zero");
    
    this->occupied_rooms = occupied_rooms;
    
    ENSURE(this->occupied_rooms == occupied_rooms, "the input occupied_rooms is equal to label occupied_rooms");
}

// --- Output ---

void MeetingPlanner::simpleOutput() {
    // PRECONDITION: attributes of meetingplanner are not Empty
    // We controleren of er kamers of meetings zijn om te rapporteren
    REQUIRE(!rooms.empty() || !meetings.empty(), "attributes of meetingplanner are not Empty");

    std::ofstream file("../output.txt");

    if (!file.is_open()) {
        std::cout << "Kan output.txt niet openen" << std::endl;
        return;
    }

    file << "MEETINGS: \n";

    for (const Meeting& meeting : meetings) {
        file << "- " << meeting.get_room();
        file << ", " << meeting.get_date() << std::endl;
        file << "  " << meeting.get_label() << std::endl;
        for (const Participation& participation : participations) {
            if (meeting.get_identifier() == participation.get_meeting()){
                file << "  " << participation.get_user();
            }
        }
        file << std::endl;
        file << "  Meeting ID:  " << meeting.get_identifier().substr(8) << std::endl;
        file << std::endl;
    }

    file << "CONFLICTING MEETINGS: \n";
    // ... (rest van je bestaande loop voor conflicting_meetings)

    file << "ROOMS: \n";
    for (const Room& room : rooms) {
        file << "- " << room.get_name() << std::endl;
        file << "  capacity: " << room.get_capacity() << " people " << std::endl;
        file << std::endl;
    }

    file.close();

    // POSTCONDITION: output.txt file got created.
    // We checken of de file daadwerkelijk bestaat op de schijf
    std::ifstream check_file("../output.txt");
    auto tussen = check_file.good();
    ENSURE(tussen, "output.txt file got created");
    check_file.close();

    std::cout << "Output geschreven naar output.txt" << std::endl;
}