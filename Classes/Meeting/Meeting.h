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

//body-gedeelte
class Meeting {
private:
    std::string label;
    std::string identifier;
    std::string room;
    std::string date;

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
     *@param label the label you want to change it to
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
   *@param label the identifier you want to change it to
   *@return None
   *precondition identifier is not empty
   *postcondition the input identifier is equal to label identifier of Meeting object
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

    void set_room(const std::string &room);

    /*
     *This function gets the date attribute
     *@param None
     *@return the date of the Meeting object
     *precondition date is not empty
     *postcondition returns this->date
     */
    [[nodiscard]] std::string get_date() const;

    void set_date(const std::string &date);

    friend bool operator==(const Meeting &lhs, const Meeting &rhs) {
        return lhs.label == rhs.label
               && lhs.identifier == rhs.identifier
               && lhs.room == rhs.room
               && lhs.date == rhs.date;
    }

    friend bool operator!=(const Meeting &lhs, const Meeting &rhs) {
        return !(lhs == rhs);
    }

    void print();
};


#endif //UITPROBEREN_MEETING_H