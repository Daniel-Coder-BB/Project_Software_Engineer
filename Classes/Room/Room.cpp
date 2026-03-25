/**
* Korte beschrijving:
 * Deze klasse stelt onze Room voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
#include "Room.h"

//body-gedeelte
/*
 *
 *
 *
 */
string Room::get_name() const {
    return name;
}

void Room::set_name(const string &name) {
    this->name = name;
}

string Room::get_identifier() const {
    return identifier;
}

void Room::set_identifier(const string &identifier) {
    this->identifier = identifier;
}

unsigned int Room::get_capacity() const {
    return capacity;
}

void Room::set_capacity(unsigned int capacity) {
    this->capacity = capacity;
}
void Room::print()
{
    std::cout<<"ROOM: "<<std::endl;
    std::cout << "Name: " << name;
    std::cout << " | Identifier: " << identifier;
    std::cout << " | Capacity: " << capacity << std::endl;
}