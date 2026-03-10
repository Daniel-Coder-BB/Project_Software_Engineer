//
// Created by danny on 10-Mar-26.
//

#include "Participation.h"

string Participation::get_user() const {
    return user;
}

void Participation::set_user(const string &user) {
    this->user = user;
}

string Participation::get_meeting() const {
    return meeting;
}

void Participation::set_meeting(const string &meeting) {
    this->meeting = meeting;
}
