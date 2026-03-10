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