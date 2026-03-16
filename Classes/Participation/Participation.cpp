/**
 * Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
#include "Participation.h"

//body-gedeelte
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
void Participation::print()
{
    std::cout<<"PARTICIPATION: "<<std::endl;
    std::cout << "User: " << user;
    std::cout << " | Meeting: " << meeting << std::endl;

}