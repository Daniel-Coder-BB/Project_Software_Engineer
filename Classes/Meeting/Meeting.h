#ifndef UITPROBEREN_MEETING_H
#define UITPROBEREN_MEETING_H

/*
 * Korte beschrijving:
 * Deze klasse stelt onze meeting voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok

#include <string>
#include "Classes/DesignByContract/DesignByContract.h"

//body-gedeelte
class Meeting {
private:
    std::string label;
    std::string identifier;
    std::string room;
    std::string date;
    int hour = 12;
    bool online = false;
    bool externals;
    bool catering;
    double co2_emission;


public:
    /*
     *This function gets the label attribute
     *@param None
     *@return the label of the Meeting object
     *precondition label is not empty
     *postcondition returns this->label
     */
    [[nodiscard]] std::string get_label() const;

    /*
     *This function changes the date attribute
     *@param the label you want to change it to
     *@return None
     *precondition label is not empty
     *postcondition the input label is equal to label attribute of Meeting object
     */
    void set_label(const std::string &label);

    /*
     *This function gets the Identifier attribute
     *@param None
     *@return the identifier of the Meeting object
     *precondition identifier is not empty
     *postcondition returns this->identifier
     */
    [[nodiscard]] std::string get_identifier() const;


  /*
   *This function changes the identifier attribute
   *@param the identifier you want to change it to
   *@return None
   *precondition identifier is not empty
   *postcondition the input identifier is equal to identifier of Meeting object
   */
    void set_identifier(const std::string &identifier);

    /*
     *This function gets the room attribute
     *@param None
     *@return the room of the Meeting object
     *precondition room is not empty
     *postcondition returns this->room
     */
    [[nodiscard]] std::string get_room() const;

   /*
    *This function changes the room attribute
    *@param the room you want to change it to
    *@return None
    *precondition room is not empty
    *postcondition the input room is equal to room of Meeting object
    */
    void set_room(const std::string &room);

    /*
     *This function gets the date attribute
     *@param None
     *@return the date of the Meeting object
     *precondition date is not empty
     *postcondition returns this->date
     */
    [[nodiscard]] std::string get_date() const;


   /*
    *This function changes the date attribute
    *@param the date you want to change it to
    *@return None
    *precondition date is not empty
    *postcondition the input date is equal to date of Meeting object
    */
    void set_date(const std::string &date);


 /*
  *This function gets the hour attribute
  *@param None
  *@return the hour of the Meeting object
  *precondition None
  *postcondition returns this->hour
  */
 [[nodiscard]] int get_hour() const;

 /*
  *This function changes the hour attribute
  *@param the hour you want to change it to
  *@return None
  *precondition hour must be between 0 and 23
  *postcondition the input hour is equal to the hour of the Meeting object
  */
 void set_hour(int hour);

 /*
  *This function gets the online status attribute
  *@param None
  *@return the online status of the Meeting object
  *precondition None
  *postcondition returns this->online
  */
 [[nodiscard]] bool is_online() const;

 /*
  *This function changes the online status attribute
  *@param the online status (true/false) you want to set
  *@return None
  *precondition None
  *postcondition the input online is equal to the online status of the Meeting object
  */
 void set_online(bool online);

 /*
  *This function gets the externals attribute
  *@param None
  *@return whether there are externals in the Meeting object
  *precondition None
  *postcondition returns this->externals
  */
 [[nodiscard]] bool is_externals() const;

 /*
  *This function changes the externals attribute
  *@param the externals status (true/false) you want to set
  *@return None
  *precondition None
  *postcondition the input externals is equal to the externals status of the Meeting object
  */
 void set_externals(bool externals);

 /*
  *This function gets the catering attribute
  *@param None
  *@return whether catering is provided for the Meeting object
  *precondition None
  *postcondition returns this->catering
  */
 [[nodiscard]] bool is_catering() const;

 /*
  *This function changes the catering attribute
  *@param the catering status (true/false) you want to set
  *@return None
  *precondition None
  *postcondition the input catering is equal to the catering status of the Meeting object
  */
 void set_catering(bool catering);

    friend bool operator==(const Meeting &lhs, const Meeting &rhs) {
        return lhs.label == rhs.label
               && lhs.identifier == rhs.identifier
               && lhs.room == rhs.room
               && lhs.date == rhs.date
               && lhs.hour == rhs.hour;;
    }

    friend bool operator!=(const Meeting &lhs, const Meeting &rhs) {
        return !(lhs == rhs);
    }




    /*
    *This function prints a string wich displays all the attributes of this Meeting object
    *@param None
    *@return None
    *precondition Meeting attributes are not empty
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
    *This function prints a calculate_co2 of this Meeting object
    *@param None
    *@return None
    *precondition Meeting attributes are not empty
    *postcondition calculate_co2 gets shown
    */
    void calculate_co2(int room_capacity, double room_co2_per_hour);
};


#endif //UITPROBEREN_MEETING_H