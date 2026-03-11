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