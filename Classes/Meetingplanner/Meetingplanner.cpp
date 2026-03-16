/**
 * Korte beschrijving:
 * Deze klasse stelt onze Meetingplanner voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
#include "MeetingPlanner.h"
#include <fstream>
#include <iostream>


void MeetingPlanner::addRoom(const Room& room) {
    rooms.push_back(room);
}

void MeetingPlanner::addMeeting(const Meeting& meeting) {
    bool cancel_meeting = false;

    for (string occupied_room: occupied_rooms) {
        if (meeting.get_room() == occupied_room) {
            cerr << "This room is occupied. Meeting cancelled"  <<endl;
            conflicting_meetings.push_back(meeting);
            cancel_meeting = true;
        }
    }
    if (!cancel_meeting) {
        meetings.push_back(meeting);
        occupied_rooms.push_back(meeting.get_room());
    }
}

void MeetingPlanner::addParticipation(const Participation& participation) {
    participations.push_back(participation);
}

std::vector<Room>& MeetingPlanner::getRooms() {
    return rooms;
}

std::vector<Meeting>& MeetingPlanner::getMeetings() {
    return meetings;
}

std::vector<Participation>& MeetingPlanner::getParticipations() {
    return participations;
}

std::vector<string> MeetingPlanner::get_occupied_rooms() const {
    return occupied_rooms;
}

void MeetingPlanner::set_occupied_rooms(const std::vector<string> &occupied_rooms) {
    this->occupied_rooms = occupied_rooms;
}

/*
 * Deze functie geeft een aparte text file die de informatie geeft van de meetings en rooms
 * @return Een text file
 */
void MeetingPlanner::simpleOutput() {
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
        file<<std::endl;
        file << "  Meeting ID:  " << meeting.get_identifier().substr(8) << std::endl;
        file << std::endl;
    }

    file << "CONFLICTING MEETINGS: \n";

    for (const Meeting& conflicting_meeting : conflicting_meetings) {
        file << "- " << conflicting_meeting.get_room();
        file << ", " << conflicting_meeting.get_date() << std::endl;
        file << "  " << conflicting_meeting.get_label() << std::endl;
        for (const Participation& participation : participations) {
            if (conflicting_meeting.get_identifier() == participation.get_meeting()){
                file << "  " << participation.get_user();
            }
        }
        file<<std::endl;
        file << "  Meeting ID:  " << conflicting_meeting.get_identifier().substr(8) << std::endl;
        file << std::endl;
    }

    file << "ROOMS: \n";

    for (const Room& room : rooms) {
        file << "- " << room.get_name() << std::endl;
        file << "  capacity: " << room.get_capacity() << " people " <<std::endl;
        file << std::endl;
    }

    file.close();

    std::cout << "Output geschreven naar output.txt" << std::endl;
}
