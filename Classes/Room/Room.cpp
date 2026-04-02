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
#include "Classes/DesignByContract/DesignByContract.h"

// body-gedeelte

string Room::get_name() const {
    // precondition name is not empty
    REQUIRE(!name.empty(), "name is not empty");

    string result = name;

    // postcondition returns this->name
    ENSURE(result == this->name, "returns this->name");
    return result;
}

void Room::set_name(const string &name) {
    // precondition name is not empty
    REQUIRE(!name.empty(), "name is not empty");

    this->name = name;

    // postcondition the input name is equal to label name of Room object
    ENSURE(this->name == name, "the input name is equal to label name of Room object");
}

string Room::get_identifier() const {
    // precondition identifier is not empty
    REQUIRE(!identifier.empty(), "identifier is not empty");

    string result = identifier;

    // postcondition returns this->identifier
    ENSURE(result == this->identifier, "returns this->identifier");
    return result;
}

void Room::set_identifier(const string &identifier) {
    // precondition identifier is not empty
    REQUIRE(!identifier.empty(), "identifier is not empty");

    this->identifier = identifier;

    // postcondition the input identifier is equal to label identifier of Room object
    ENSURE(this->identifier == identifier, "the input identifier is equal to label identifier of Room object");
}

 int Room::get_capacity() const {
    // precondition capacity is not empty (voor een unsigned int betekent dit meestal > 0)
    REQUIRE(capacity >= 0, "capacity is not empty");

     int result = capacity;

    // postcondition returns this->capacity
    ENSURE(result == this->capacity, "returns this->capacity");
    return result;
}

void Room::set_capacity( int capacity) {
    // precondition capacity is bigger or equal to zero
    REQUIRE(capacity >= 0, "capacity is bigger or equal to zero");

    this->capacity = capacity;

    // postcondition the input capacity is equal to label capacity of Room object
    ENSURE(this->capacity == capacity, "the input capacity is equal to label capacity of Room object");
}

string Room::get_campus() const {
    return campus;
}

void Room::set_campus(const string &campus) {
    this->campus = campus;
}

string Room::get_buulding() const {
    return building;
}

void Room::set_buulding(const string &buulding) {
    this->building = buulding;
}


void Room::print() {
    // Preconditie check op basis van de attributen (consistent met andere klassen)
    REQUIRE(!name.empty() && !identifier.empty() && capacity >= 0, "Room attributes are not empty");

    std::cout << "ROOM: " << std::endl;
    std::cout << "Name: " << name;
    std::cout << " | Identifier: " << identifier;
    std::cout << " | Capacity: " << capacity << std::endl;
}

