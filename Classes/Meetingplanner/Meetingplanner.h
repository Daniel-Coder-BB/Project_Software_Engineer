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
#include "Classes/Campus/Campus.h"
#include "Classes/Buildings/Buildings.h"
#include <string>

#include "Classes/CateringProviders/Cateringproviders.h"
#include "Classes/Renovations/Renovations.h"

//body-gedeelte
class MeetingPlanner {
private:
    std::vector<Room> rooms;
    std::vector<Meeting> meetings;
    std::vector<Participation> participations;
    std::vector<string> occupied_rooms;
    std::vector<Meeting> conflicting_meetings;
    std::vector<Campus> campuses;
    std::vector<Buildings> buildings;
    std::vector<Renovations> renovations;
    std::vector<Cateringproviders> catering;




public:
    /*
    *This function changes the room attribute
    *@param the room you want to change it to
    *@return None
    *precondition room is not empty
    *postcondition the input room is equal to room of Meetingplanner object
    */
    void addRoom(const Room& room);

    /*
    *This function changes the meeting attribute
    *@param the meeting you want to change it to
    *@return None
    *precondition meeting is not empty
    *postcondition the input meeting is equal to meeting of Meetingplanner object
    */
    void addMeeting(const Meeting& meeting);

    /*
    *This function changes the participation attribute
    *@param the participation you want to change it to
    *@return None
    *precondition participation is not empty
    *postcondition the input participation is equal to participation of Meetingplanner object
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

    /*
    *This function gets the occupied_rooms attribute
    *@param None
    *@return the occupied_rooms of the Meetingplanner object
    *precondition occupied_rooms is not empty
    *postcondition returns this->occupied_rooms
    */
    std::vector<string> get_occupied_rooms() const;

    /*
   *This function changes the occupied_rooms attribute
   *@param the occupied_rooms you want to change it to
   *@return None
   *precondition occupied_rooms is bigger or equal to zero
   *postcondition the input occupied_rooms is equal to occupied_rooms of Meetingplanner object
   */
    void set_occupied_rooms(const std::vector<string> &occupied_rooms);

 /*
     * This function returns the list of campuses
     * @return a vector containing all Campus objects
     * precondition None.
     * postcondition returns a vector of campuses.
     */
 std::vector<Campus> get_campuses() const;

 /*
 * This function adds a campus to the system
 * @param campus the Campus object to be added
 * precondition None.
 * postcondition the campus is added to the list of campuses.
 */
 void set_campuses(const Campus &campus);

 /*
 * This function returns the list of buildings
 * @return a vector containing all Building objects
 * precondition None.
 * postcondition returns a vector of buildings.
 */
 std::vector<Buildings> get_buildings() const;

 /*
 * This function adds a building to the system
 * @param building the Building object to be added
 * precondition None.
 * postcondition the building is added to the list of buildings.
 */
 void set_buildings(const Buildings &building);

    /*
        * This function returns the list of renovations
        * @return a vector containing all Renovation objects
        * precondition None.
        * postcondition returns a vector of renovations.
        */
    std::vector<Renovations> get_renovations();

    /*
    * This function adds a renovation to the system
    * @param renovation the Renovation object to be added
    * precondition None.
    * postcondition the renovation is added to the list of renovations.
    */
    void set_renovations(const Renovations &renovation);

    /*
        * This function returns the list of catering providers
        * @return a vector containing all Cateringproviders objects
        * precondition None.
        * postcondition returns a vector of catering providers.
        */
    std::vector<Cateringproviders> get_catering() const;

    /*
    * This function adds a catering provider to the system
    * @param catering the Cateringproviders object to be added
    * precondition None.
    * postcondition the catering provider is added to the list of catering providers.
    */
    void set_catering(const Cateringproviders &catering);

    friend bool operator==(const MeetingPlanner &lhs, const MeetingPlanner &rhs) {
        return lhs.rooms == rhs.rooms
               && lhs.meetings == rhs.meetings
               && lhs.participations == rhs.participations
               && lhs.occupied_rooms == rhs.occupied_rooms;

    }




    friend bool operator!=(const MeetingPlanner &lhs, const MeetingPlanner &rhs) {
        return !(lhs == rhs);
    }

     /*
    *This function writes an output to an .txt file
    *@param None
    *@return None
    *precondition attributes of meetingplanner are not Empty
    *postcondition output.txt file got created.
    */
    void simpleOutput();

    /*
    *This function writes an structure to an .dot file
    *@param None
    *@return None
    *precondition attributes of meetingplanner are not Empty
    *postcondition structure.dot file got created.
    */
    void exportGraphviz();

    /*
    *This function processes meetings
    *@param None
    *@return None
    *precondition attributes of meetingplanner are not Empty
    *postcondition  Meetings are processesed.
    */
    void processMeetings();
};


#endif