#ifndef ROOM_H
#define ROOM_H

/**
 * Korte beschrijving:
 * Deze klasse stelt onze Room voor.
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
class Room {
private:
    string name;
    string identifier;
    unsigned int capacity;

public:
    /*
     *This function gets the name attribute
     *@param None
     *@return the name of the Room object
     *precondition name is not empty
     *postcondition returns this->name
     */
    string get_name() const;
    /*
     *This function sets the name attribute
     *@param g
     *@return the name of the Room object
     *precondition name is not empty
     *postcondition returns this->name
     */
    void set_name(const string &name);
    /*
     *This function gets the identifier attribute
     *@param None
     *@return the identifier of the Room object
     *precondition identifier is not empty
     *postcondition returns this->identifier
     */
    string get_identifier() const;

    void set_identifier(const string &identifier);
    /*
     *This function gets the capacity attribute
     *@param None
     *@return the capacity of the Room object
     *precondition capacity is not empty
     *postcondition returns this->capacity
     */
    unsigned int get_capacity() const;

    void set_capacity(unsigned int capacity);

    friend bool operator==(const Room &lhs, const Room &rhs) {
        return lhs.name == rhs.name
               && lhs.identifier == rhs.identifier
               && lhs.capacity == rhs.capacity;
    }

    friend bool operator!=(const Room &lhs, const Room &rhs) {
        return !(lhs == rhs);
    }

    void print();
};



#endif //ROOM_H
