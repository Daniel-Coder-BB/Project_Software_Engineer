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
    return name;
}

void Buildings::set_name(const std::string &name) {
    this->name = name;
}

std::string Buildings::get_identifier() const {
    return identifier;
}

void Buildings::set_identifier(const std::string &identifier) {
    this->identifier = identifier;
}

std::string Buildings::get_campus() const {
    return campus;
}

void Buildings::set_campus(const std::string &campus) {
    this->campus = campus;
}
