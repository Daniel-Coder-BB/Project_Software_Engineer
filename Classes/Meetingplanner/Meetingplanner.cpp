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
#include <pstl/execution_defs.h>


void MeetingPlanner::addRoom(const Room& room) {
    rooms.push_back(room);
}

void MeetingPlanner::addMeeting(const Meeting& meeting) {
    meetings.push_back(meeting);
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

void MeetingPlanner::simpleOutput() {
    std::ofstream file("output.txt");

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

    file << "ROOMS: \n";

    for (const Room& room : rooms) {
        file << "- " << room.get_name() << std::endl;
        file << "  capacity: " << room.get_capacity() << " people " <<std::endl;
        file << std::endl;
    }

    file.close();

    std::cout << "Output geschreven naar output.txt" << std::endl;
}