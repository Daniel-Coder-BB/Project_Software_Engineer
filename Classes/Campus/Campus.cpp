/*
* Korte beschrijving:
 * Deze klasse stelt onze campus voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

//includ blok
#include "Campus.h"
#include "Classes/DesignByContract/DesignByContract.h"

std::string Campus::get_name() const {
    return name;
}

void Campus::set_name(const std::string &name) {
    this->name = name;
}

std::string Campus::get_identifier() const {
    return identifier;
}

void Campus::set_identifier(const std::string &identifier) {
    this->identifier = identifier;
}
