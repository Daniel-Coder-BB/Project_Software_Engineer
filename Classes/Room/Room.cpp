//
// Created by danny on 09-Mar-26.
//

#include "Room.h"

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