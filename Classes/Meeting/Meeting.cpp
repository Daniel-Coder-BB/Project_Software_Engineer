/**
* Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

#include "Meeting.h"
#include "Classes/DesignByContract/DesignByContract.h" // Zorg dat dit de juiste naam is
#include <iostream>

// --- Getters ---

std::string Meeting::get_label() const {
    REQUIRE(!label.empty(), "label is not empty");
    std::string result = label;
    ENSURE(result == this->label, "returns this->label");
    return result;
}

std::string Meeting::get_identifier() const {
    REQUIRE(!identifier.empty(), "identifier is not empty");
    std::string result = identifier;
    ENSURE(result == this->identifier, "returns this->identifier");
    return result;
}

std::string Meeting::get_room() const {
    REQUIRE(!room.empty(), "room is not empty");
    std::string result = room;
    ENSURE(result == this->room, "returns this->room");
    return result;
}

std::string Meeting::get_date() const {
    REQUIRE(!date.empty(), "date is not empty");
    std::string result = date;
    ENSURE(result == this->date, "returns this->date");
    return result;
}

// --- Setters ---

void Meeting::set_label(const std::string &label) {
    REQUIRE(!label.empty(), "label is not empty");
    this->label = label;
    ENSURE(this->label == label, "the input label is equal to label attribute");
}

void Meeting::set_identifier(const std::string &identifier) {
    REQUIRE(!identifier.empty(), "identifier is not empty");
    this->identifier = identifier;
    ENSURE(this->identifier == identifier, "the input identifier is equal to identifier attribute");
}

void Meeting::set_room(const std::string &room) {
    REQUIRE(!room.empty(), "room is not empty");
    this->room = room;
    ENSURE(this->room == room, "the input room is equal to room attribute");
}

void Meeting::set_date(const std::string &date) {
    REQUIRE(!date.empty(), "date is not empty");
    this->date = date;
    ENSURE(this->date == date, "the input date is equal to date attribute");
}

// --- Overige functies ---

void Meeting::print() {
    // Preconditie: attributes mogen niet leeg zijn
    REQUIRE(!label.empty() && !identifier.empty() && !room.empty() && !date.empty(),
            "Meeting attributes are not empty");

    std::cout << "MEEETING" << std::endl;
    std::cout << "Label: " << label;
    std::cout << " | Identifier: " << identifier;
    std::cout << " | Room: " << room;
    std::cout << " | Date: " << date << std::endl;

    // Postconditie: "string gets shown" is lastig te testen in code,
    // maar we kunnen bevestigen dat de functie het einde heeft bereikt.
}