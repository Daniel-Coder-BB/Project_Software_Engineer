#ifndef PLANNING_SYSTEM_PROJECT_RENOVATIONS_H
#define PLANNING_SYSTEM_PROJECT_RENOVATIONS_H

/*
* Korte beschrijving:
 * Deze klasse stelt onze Renovations voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

#include <iostream>
#include <string>
using namespace std;


class Renovations {
private:
 string room;
 string start;
 string end;

public:
 /*
     *This function gets the room attribute
     *@param None
     *@return the room of the Renovations object
     *precondition room is not empty
     *postcondition returns this->room
     */
 [[nodiscard]] string get_room() const;


 /*
     *This function changes the room attribute
     *@param room the room you want to change it to
     *@return None
     *precondition room is not empty
     *postcondition the input room is equal to room attribute of Renovation object
     */
 void set_room(const string &room);
     /*
      *This function gets the start attribute
      *@param None
      *@return the start of the Renovations object
      *precondition start is not empty
      *postcondition returns this->start
      */
 [[nodiscard]] string get_start() const;

        /*
         *This function changes the start attribute
         *@param start the start you want to change it to
         *@return None
         *precondition start is not empty
         *postcondition the input start is equal to start attribute of Meeting object
         */
 void set_start(const string &start);


    /*
     *This function gets the end attribute
     *@param None
     *@return the end of the Renovations object
     *precondition end is not empty
     *postcondition returns this->end
     */
 [[nodiscard]] string get_end() const;

    /*
     *This function changes the end attribute
     *@param end the end you want to change it to
     *@return None
     *precondition end is not empty
     *postcondition the input end is equal to end attribute of Renovations object
     */
 void set_end(const string &end);
};


#endif //PLANNING_SYSTEM_PROJECT_RENOVATIONS_H