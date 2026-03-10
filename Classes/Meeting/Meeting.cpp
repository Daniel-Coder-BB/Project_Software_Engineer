//
// Created by danny on 10-Mar-26.
//

#include "Meeting.h"

string Meeting::get_label() const {
    return label;
}

void Meeting::set_label(const string &label) {
    this->label = label;
}

string Meeting::get_identifier() const {
    return identifier;
}

void Meeting::set_identifier(const string &identifier) {
    this->identifier = identifier;
}

string Meeting::get_room() const {
    return room;
}

void Meeting::set_room(const string &room) {
    this->room = room;
}
