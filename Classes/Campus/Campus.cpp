/*
* Korte beschrijving:
 * Deze klasse stelt onze campus voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

#include "Campus.h"
#include "Classes/DesignByContract/DesignByContract.h"

std::string Campus::get_name() const {
    // ENSURE: returns this->name
    return name;
}

void Campus::set_name(const std::string &name) {
    // REQUIRE: name is not empty
    REQUIRE(!name.empty(), "Precondition failure: name cannot be empty");

    this->name = name;

    // ENSURE: the input name is equal to the attribute of Campus
    ENSURE(this->name == name, "Postcondition failure: name attribute not set correctly");
}

std::string Campus::get_identifier() const {
    // ENSURE: returns this->identifier
    return identifier;
}

void Campus::set_identifier(const std::string &identifier) {
    // REQUIRE: identifier is not empty
    REQUIRE(!identifier.empty(), "Precondition failure: identifier cannot be empty");

    this->identifier = identifier;

    // ENSURE: the input identifier is equal to the attribute of Campus
    ENSURE(this->identifier == identifier, "Postcondition failure: identifier attribute not set correctly");
}