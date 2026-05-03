/*
* Korte beschrijving:
 * Deze klasse stelt onze buildings voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

#include "Buildings.h"
#include "Classes/DesignByContract/DesignByContract.h"

std::string Buildings::get_name() const {
    // ENSURE: returns this->name
    return name;
}

void Buildings::set_name(const std::string &name) {
    // REQUIRE: name is not empty
    REQUIRE(!name.empty(), "Precondition failure: name cannot be empty");

    this->name = name;

    // ENSURE: the input name is equal to name of Buildings
    ENSURE(this->name == name, "Postcondition failure: name attribute not set correctly");
}

std::string Buildings::get_identifier() const {
    // ENSURE: returns this->identifier
    return identifier;
}

void Buildings::set_identifier(const std::string &identifier) {
    // REQUIRE: identifier is not empty
    REQUIRE(!identifier.empty(), "Precondition failure: identifier cannot be empty");

    this->identifier = identifier;

    // ENSURE: the input identifier is equal to identifier of Buildings
    ENSURE(this->identifier == identifier, "Postcondition failure: identifier attribute not set correctly");
}

std::string Buildings::get_campus() const {
    // ENSURE: returns this->campus
    return campus;
}

void Buildings::set_campus(const std::string &campus) {
    // REQUIRE: campus is not empty
    REQUIRE(!campus.empty(), "Precondition failure: campus cannot be empty");

    this->campus = campus;

    // ENSURE: the input campus is equal to campus of Buildings
    ENSURE(this->campus == campus, "Postcondition failure: campus attribute not set correctly");
}