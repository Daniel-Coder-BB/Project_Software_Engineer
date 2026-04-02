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
    int capacity = -1;
    string campus;
    string building;

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
   *This function changes the name attribute
   *@param the name you want to change it to
   *@return None
   *precondition name is not empty
   *postcondition the input name is equal to label name of Room object
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
    /*
   *This function changes the identifier attribute
   *@param the identifier you want to change it to
   *@return None
   *precondition identifier is not empty
   *postcondition the input identifier is equal to label identifier of Room object
   */
    void set_identifier(const string &identifier);
    /*
     *This function gets the capacity attribute
     *@param None
     *@return the capacity of the Room object
     *precondition capacity is not empty
     *postcondition returns this->capacity
     */
     int get_capacity() const;
    /*
   *This function changes the capacity attribute
   *@param the capacity you want to change it to
   *@return None
   *precondition capacity is bigger or equal to zero
   *postcondition the input capacity is equal to label capacity of Room object
   */
    void set_capacity( int capacity);

    friend bool operator==(const Room &lhs, const Room &rhs) {
        return lhs.name == rhs.name
               && lhs.identifier == rhs.identifier
               && lhs.capacity == rhs.capacity;
    }

    friend bool operator!=(const Room &lhs, const Room &rhs) {
        return !(lhs == rhs);
    }
    /*
    *This function prints a string wich displays all the attributes of this Room object
    *@param None
    *@return None
    *precondition Room attributes are not empty
    *postcondition string with all the attributes gets shown
    */
    void print();

    /*
     *This function gets the campus attribute
     *@param None
     *@return the campus of the Buildings
     *precondition campus is not empty
     *postcondition returns this->campus
     */
    [[nodiscard]] string get_campus() const;

    /*
    *This function changes the campus attribute
    *@param the campus you want to change it to
    *@return None
    *precondition campus is not empty
    *postcondition the input campus is equal to campus attribute of Room
    */
    void set_campus(const string &campus);

    /*
     *This function gets the building attribute
     *@param None
     *@return the building attribute of the Room
     *precondition building is not empty
     *postcondition returns this->building
     */
    [[nodiscard]] string get_buulding() const;

    /*
    *This function changes the building attribute
    *@param the building you want to change it to
    *@return None
    *precondition building is not empty
    *postcondition the input campus is equal to building attribute of Room
    */
    void set_building(const string &building);
};



#endif //ROOM_H
