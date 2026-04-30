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
#include "Classes/DesignByContract/DesignByContract.h"

//Getters

string Participation::get_user() const {
    // precondition user is not empty
    REQUIRE(!user.empty(), "user is not empty");

    string result = user;

    // postcondition returns this->user
    ENSURE(result == this->user, "returns this->user");
    return result;
}

string Participation::get_meeting() const {
    // precondition meeting is not empty
    REQUIRE(!meeting.empty(), "meeting is not empty");

    string result = meeting;

    // postcondition returns this->meeting
    ENSURE(result == this->meeting, "returns this->meeting");
    return result;
}

//Setters

void Participation::set_user(const string &user) {
    // precondition user is not empty
    REQUIRE(!user.empty(), "user is not empty");

    this->user = user;

    // postcondition the input user is equal to label user of Participation object
    ENSURE(this->user == user, "the input user is equal to label user of Participation object");
}

void Participation::set_meeting(const string &meeting) {
    // precondition meeting is not empty
    REQUIRE(!meeting.empty(), "meeting is not empty");

    this->meeting = meeting;

    // postcondition the input meeting is equal to label meeting of Participation object
    ENSURE(this->meeting == meeting, "the input meeting is equal to label meeting of Participation object");
}

//Overige functies

void Participation::print() {
    // precondition Meeting attributes are not empty (overgenomen van vergelijkbare klassen)
    REQUIRE(!user.empty() && !meeting.empty(), "Participation attributes are not empty");

    std::cout << "PARTICIPATION: " << std::endl;
    std::cout << "User: " << user;
    std::cout << " | Meeting: " << meeting << std::endl;

    // postcondition string with all the attributes gets shown
}