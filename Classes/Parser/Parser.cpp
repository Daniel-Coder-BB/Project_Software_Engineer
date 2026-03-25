//
// Created by danny on 25-Mar-26.
//

#include "Parser.h"

string Parser::get_filename() const {
    return filename;
}

void Parser::set_filename(const string &filename) {
    this->filename = filename;
}
