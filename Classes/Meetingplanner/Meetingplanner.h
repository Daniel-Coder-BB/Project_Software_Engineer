#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

/**
 * Korte beschrijving:
 * Deze klasse stelt onze Meetingplanner voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
#include <vector>
#include "Classes//Room/Room.h"
#include "Classes//Meeting/Meeting.h"
#include "Classes//Participation/Participation.h"
#include <string>

class MeetingPlanner {
private:
    std::vector<Room> rooms;
    std::vector<Meeting> meetings;
    std::vector<Participation> participations;
    std::vector<string> occupied_rooms;
    std::vector<Meeting> conflicting_meetings;

public:
    void addRoom(const Room& room);
    void addMeeting(const Meeting& meeting);
    void addParticipation(const Participation& participation);

    std::vector<Room>& getRooms();
    std::vector<Meeting>& getMeetings();
    std::vector<Participation>& getParticipations();



    std::vector<string> get_occupied_rooms() const;

    void set_occupied_rooms(const std::vector<string> &occupied_rooms);

    friend bool operator==(const MeetingPlanner &lhs, const MeetingPlanner &rhs) {
        return lhs.rooms == rhs.rooms
               && lhs.meetings == rhs.meetings
               && lhs.participations == rhs.participations
               && lhs.occupied_rooms == rhs.occupied_rooms;
    }

    friend bool operator!=(const MeetingPlanner &lhs, const MeetingPlanner &rhs) {
        return !(lhs == rhs);
    }

    void simpleOutput();
};

#endif