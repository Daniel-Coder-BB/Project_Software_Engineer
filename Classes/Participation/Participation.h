#ifndef PARTICIPATION_H
#define PARTICIPATION_H

/**
 * Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
#include <iostream>
#include <string>

// Globale using statements
using namespace std;

//body-gedeelte
class Participation {
private:
    string user;
    string meeting;
public:

    /*
     *This function gets the user attribute
     *@param None
     *@return the user of the Participation object
     *precondition user is not empty
     *postcondition returns this->user
     */
    string get_user() const;

    /*
    *This function changes the user attribute
    *@param label the user you want to change it to
    *@return None
    *precondition user is not empty
    *postcondition the input user is equal to label user of Participation object
    */
    void set_user(const string &user);

     /*
     *This function gets the meeting attribute
     *@param None
     *@return the meeting of the Participation object
     *precondition meeting is not empty
     *postcondition returns this->meeting
     */
    string get_meeting() const;

    /*
    *This function changes the meeting attribute
    *@param label the meeting you want to change it to
    *@return None
    *precondition meeting is not empty
    *postcondition the input meeting is equal to label meeting of Participation object
    */
    void set_meeting(const string &meeting);

    friend bool operator==(const Participation &lhs, const Participation &rhs) {
        return lhs.user == rhs.user
               && lhs.meeting == rhs.meeting;
    }

    friend bool operator!=(const Participation &lhs, const Participation &rhs) {
        return !(lhs == rhs);
    }
    /*
    *This function prints a string wich displays all the attributes of this Participation object
    *@param None
    *@return None
    *precondition Participation attributes are not empty
    *postcondition string with all the attributes gets shown
    */
    void print();
};



#endif //PARTICIPATION_H
