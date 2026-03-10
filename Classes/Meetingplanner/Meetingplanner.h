#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H


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