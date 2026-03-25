/*
* Korte beschrijving:
 *Dit stelt onze parser klasse voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 25/03/2026
 * @version 1.5
 */

#include "Parser.h"

string Parser::get_filename() const {
    return filename;
}

void Parser::set_filename(const string &filename) {
    this->filename = filename;
}
