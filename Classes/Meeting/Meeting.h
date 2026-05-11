#ifndef UITPROBEREN_MEETING_H
#define UITPROBEREN_MEETING_H

/*
 * Korte beschrijving:
 * Deze klasse stelt onze meeting voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/05/2026
 * @version 2.0
 */

// Include blok

#include <string>
#include <vector>
#include "Classes/DesignByContract/DesignByContract.h"

class Room;
class Renovations;

//body-gedeelte
class Meeting {
private:
    std::string label;
    std::string identifier;
    std::string room;
    std::string date;
    int hour = 12;
    bool online = false;
    bool catering = false;
    double co2_emission = 0.0;


public:

    /*
     *This function gets the label attribute
     *@param None
     *@return the label of the Meeting object
     *precondition label is not empty
     *REQUIRE(!label.empty(), "label is not empty")
     *postcondition returns this->label
     *ENSURE(result == this->label, "returns this->label")
     */
    [[nodiscard]] std::string get_label() const;

    /*
     *This function changes the date attribute
     *@param the label you want to change it to
     *@return None
     *precondition label is not empty
     *REQUIRE(!label.empty(), "label is not empty")
     *postcondition the input label is equal to label attribute of Meeting object
     *ENSURE(this->label == label, "label correctly set")
     */
    void set_label(const std::string &label);

    /*
     *This function gets the Identifier attribute
     *@param None
     *@return the identifier of the Meeting object
     *precondition identifier is not empty
     *REQUIRE(!identifier.empty(), "identifier is not empty")
     *postcondition returns this->identifier
     *ENSURE(result == this->identifier, "returns this->identifier"
     */
    [[nodiscard]] std::string get_identifier() const;

    /*
   *This function changes the identifier attribute
   *@param the identifier you want to change it to
   *@return None
   *precondition identifier is not empty
   *REQUIRE(!identifier.empty(), "identifier is not empty")
   *postcondition the input identifier is equal to identifier of Meeting object
   *ENSURE(this->identifier == identifier, "identifier correctly set")
   */
    void set_identifier(const std::string &identifier);

    /*
     *This function gets the room attribute
     *@param None
     *@return the room of the Meeting object
     *precondition room is not empty
     *REQUIRE(online || !room.empty(), "room must be set if meeting is not online")
     *postcondition returns this->room
     *ENSURE(result == this->room, "returns this->room")
     */
    [[nodiscard]] std::string get_room() const;

    /*
    *This function changes the room attribute
    *@param the room you want to change it to
    *@return None
    *precondition room is not empty
    *REQUIRE(!room.empty(), "room is not empty")
    *postcondition the input room is equal to room of Meeting object
    *ENSURE(this->room == room, "room correctly set")
    */
    void set_room(const std::string &room);

    /*
     *This function gets the date attribute
     *@param None
     *@return the date of the Meeting object
     *precondition date is not empty
     *REQUIRE(!date.empty(), "date is not empty")
     *postcondition returns this->date
     *ENSURE(result == this->date, "returns this->date")
     */
    [[nodiscard]] std::string get_date() const;

    /*
    *This function changes the date attribute
    *@param the date you want to change it to
    *@return None
    *precondition date is not empty
    *REQUIRE(!date.empty(), "date is not empty")
    *postcondition the input date is equal to date of Meeting object
    *ENSURE(this->date == date, "date correctly set")
    */
    void set_date(const std::string &date);

    /*
    *This function gets the hour attribute
    *@param None
    *@return the hour of the Meeting object
    *precondition None
    *postcondition returns this->hour
    *ENSURE(hour >= 0 && hour <= 23, "hour is within valid range")
    */
    [[nodiscard]] int get_hour() const;

    /*
    *This function changes the hour attribute
    *@param the hour you want to change it to
    *@return None
    *precondition hour must be between 0 and 23
    *REQUIRE(hour >= 0 && hour <= 23, "hour must be between 0 and 23")
    *postcondition the input hour is equal to the hour of the Meeting object
    *ENSURE(this->hour == hour, "hour correctly set")
    */
    void set_hour(int hour);

    /*
    *This function gets the online status attribute
    *@param None
    *@return the online status of the Meeting object
    *precondition None
    *postcondition returns this->online
    *ENSURE(online == true || online == false, "online is a valid boolean")
    */
    [[nodiscard]] bool is_online() const;

    /*
    *This function changes the online status attribute
    *@param the online status (true/false) you want to set
    *@return None
    *precondition None
    *postcondition the input online is equal to the online status of the Meeting object
    *ENSURE(this->online == online, "online status correctly set")
    */
    void set_online(bool online);

    /*
    *This function gets the catering attribute
    *@param None
    *@return whether catering is provided for the Meeting object
    *precondition None
    *postcondition returns this->catering
    *ENSURE(catering == true || catering == false, "catering is a valid boolean")
    */
    [[nodiscard]] bool is_catering() const;

    /*
    *This function changes the catering attribute
    *@param the catering status (true/false) you want to set
    *@return None
    *precondition None
    *postcondition the input catering is equal to the catering status of the Meeting object
    *ENSURE(this->catering == catering, "catering status correctly set")
    */
    void set_catering(bool catering);


    friend bool operator==(const Meeting &lhs, const Meeting &rhs) {
        return lhs.label == rhs.label
               && lhs.identifier == rhs.identifier
               && lhs.room == rhs.room
               && lhs.date == rhs.date
               && lhs.hour == rhs.hour;
    }

    friend bool operator!=(const Meeting &lhs, const Meeting &rhs) {
        return !(lhs == rhs);
    }

    /*
    *This function prints a string wich displays all the attributes of this Meeting object
    *@param None
    *@return None
    *precondition Meeting attributes are valid
    *postcondition string with all the attributes gets shown
    */
    void print();

    /*
    *This function gets the co2
    *@param None
    *@return the co2 of the Meeting object
    *precondition None
    *postcondition returns this->co2
    */
    double get_co2() const;

    /*
    *This function gets the capacity of the meeting room
    *@param vector with rooms
    *@return the capacity of the room
    *precondition rooms vector is not empty
    *postcondition returns room capacity or 0
    */
    int get_capacity(const std::vector<Room>& rooms) const;

    /*
    *This function calculates the CO2 emission
    *@param amount of participants
    *@return calculated co2
    *precondition online meetings cannot have catering
    *postcondition returns a non-negative co2 value
    */
    double calculateCO2(int participants) const;

    /*
    *This function calculates the catering cost
    *@param amount of participants
    *@return catering cost
    *precondition online meetings cannot have catering
    *postcondition returns a non-negative catering cost
    */
    double calculateCateringCost(int participants) const;

    /*
    *This function checks if the meeting can take place
    *@param occupied rooms and renovations
    *@return true if possible, false otherwise
    *precondition None
    *postcondition returns a valid boolean
    */
    bool canTakePlace(
            const std::vector<std::string>& occupied_rooms,
            const std::vector<Renovations>& renovations
    ) const;
};

#endif //UITPROBEREN_MEETING_H