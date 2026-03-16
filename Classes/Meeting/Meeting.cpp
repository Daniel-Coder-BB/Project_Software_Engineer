/**
 * Korte beschrijving:
 * Deze klasse stelt onze meeting voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
#include "Meeting.h"
#include <iostream>

//body-gedeelte
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
void Meeting::print()
{
    std::cout << "MEEETING"<<std::endl;
    std::cout << "Label: " << label;
    std::cout << " | Identifier: " << identifier;
    std::cout << " | Room: " << room;
    std::cout << " | Date: " << date << std::endl;
}