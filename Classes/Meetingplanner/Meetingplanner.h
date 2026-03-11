#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

/**
 * Korte beschrijving:
 * Deze klasse stelt een Meetingplanner voor.
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

class MeetingPlanner {
private:
    std::vector<Room> rooms;
    std::vector<Meeting> meetings;
    std::vector<Participation> participations;

public:
    void addRoom(const Room& room);
    void addMeeting(const Meeting& meeting);
    void addParticipation(const Participation& participation);

    std::vector<Room>& getRooms();
    std::vector<Meeting>& getMeetings();
    std::vector<Participation>& getParticipations();
};

#endif