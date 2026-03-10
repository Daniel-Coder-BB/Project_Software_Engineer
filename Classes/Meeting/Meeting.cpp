//
// Created by ibrab on 10.03.2026.
//

#include "Meeting.h"

std::string Meeting::get_label() const {
    return label;
}

void Meeting::set_label(const std::string &label) {
    this->label = label;
}

std::string Meeting::get_identifier() const {
    return identifier;
}

void Meeting::set_identifier(const std::string &identifier) {
    this->identifier = identifier;
}

std::string Meeting::get_room() const {
    return room;
}

void Meeting::set_room(const std::string &room) {
    this->room = room;
}

std::string Meeting::get_date() const {
    return date;
}

void Meeting::set_date(const std::string &date) {
    this->date = date;
}
