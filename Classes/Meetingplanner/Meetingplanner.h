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

//body-gedeelte
class MeetingPlanner {
private:
    std::vector<Room> rooms;
    std::vector<Meeting> meetings;
    std::vector<Participation> participations;
    std::vector<string> occupied_rooms;
    std::vector<Meeting> conflicting_meetings;

public:
    /*
    *This function changes the room attribute
    *@param label the room you want to change it to
    *@return None
    *precondition room is not empty
    *postcondition the input room is equal to label room of Meetingplanner object
    */
    void addRoom(const Room& room);

    /*
    *This function changes the meeting attribute
    *@param label the meeting you want to change it to
    *@return None
    *precondition meeting is not empty
    *postcondition the input meeting is equal to label meeting of Meetingplanner object
    */
    void addMeeting(const Meeting& meeting);

    /*
    *This function changes the participation attribute
    *@param label the participation you want to change it to
    *@return None
    *precondition participation is not empty
    *postcondition the input participation is equal to label participation of Meetingplanner object
    */
    void addParticipation(const Participation& participation);

    /*
     *This function gets the rooms attribute
     *@param None
     *@return the rooms of the Meetingplanner object
     *precondition rooms is not empty
     *postcondition returns this->rooms
     */
    std::vector<Room>& getRooms();

    /*
     *This function gets the meetings attribute
     *@param None
     *@return the meetings of the Meetingplanner object
     *precondition meetings is not empty
     *postcondition returns this->meetings
     */
    std::vector<Meeting>& getMeetings();

    /*
     *This function gets the participations attribute
     *@param None
     *@return the participations of the Meetingplanner object
     *precondition participations is not empty
     *postcondition returns this->participations
     */
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