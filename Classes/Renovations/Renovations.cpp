/*
* Korte beschrijving:
 * Deze klasse stelt onze Renovations voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

#include "Renovations.h"
#include "Classes/DesignByContract/DesignByContract.h"

string Renovations::get_room() const {
 // ENSURE: returns this->room
 ENSURE(!this->room.empty(), "Postcondition failure: room is empty");
 return room;
}

void Renovations::set_room(const string &room) {
 // REQUIRE: room is not empty
 REQUIRE(!room.empty(), "Precondition failure: room cannot be empty");

 this->room = room;

 // ENSURE: the input room is equal to room attribute
 ENSURE(this->room == room, "Postcondition failure: room attribute not set correctly");
}

string Renovations::get_start() const {
 // ENSURE: returns this->start
 return start;
}

void Renovations::set_start(const string &start) {
 // REQUIRE: start is not empty
 REQUIRE(!start.empty(), "Precondition failure: start time cannot be empty");

 this->start = start;

 // ENSURE: the input start is equal to start attribute
 ENSURE(this->start == start, "Postcondition failure: start attribute not set correctly");
}

string Renovations::get_end() const {
 // ENSURE: returns this->end
 return end;
}

void Renovations::set_end(const string &end) {
 // REQUIRE: end is not empty
 REQUIRE(!end.empty(), "Precondition failure: end time cannot be empty");

 this->end = end;

 // ENSURE: the input end is equal to end attribute
 ENSURE(this->end == end, "Postcondition failure: end attribute not set correctly");
}