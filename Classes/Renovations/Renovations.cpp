/*
* Korte beschrijving:
 * Deze klasse stelt onze Renovations voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

#include "Renovations.h"

string Renovations::get_room() const {
 return room;
}

void Renovations::set_room(const string &room) {
 this->room = room;
}

string Renovations::get_start() const {
 return start;
}

void Renovations::set_start(const string &start) {
 this->start = start;
}

string Renovations::get_end() const {
 return end;
}

void Renovations::set_end(const string &end) {
 this->end = end;
}
