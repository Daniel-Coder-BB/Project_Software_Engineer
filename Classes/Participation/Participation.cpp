/**
 * Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 2.0
 */

#include "Participation.h"
#include "Classes/DesignByContract/DesignByContract.h"

//Getters

std::string Participation::get_user() const {

    REQUIRE(!user.empty(), "user is not empty");

    std::string result = user;

    ENSURE(result == this->user,
           "returns this->user");

    return result;
}

std::string Participation::get_meeting() const {

    REQUIRE(!meeting.empty(),
            "meeting is not empty");

    std::string result = meeting;

    ENSURE(result == this->meeting,
           "returns this->meeting");

    return result;
}

//Setters

void Participation::set_user(const std::string &user) {

    REQUIRE(!user.empty(),
            "user is not empty");

    this->user = user;

    ENSURE(this->user == user,
           "the input user is equal to label user of Participation object");
}

void Participation::set_meeting(const std::string &meeting) {

    REQUIRE(!meeting.empty(),
            "meeting is not empty");

    this->meeting = meeting;

    ENSURE(this->meeting == meeting,
           "the input meeting is equal to label meeting of Participation object");
}


int Participation::countParticipants(
        const std::vector<Participation>& participations,
        const std::string& meeting_id) {

    REQUIRE(!meeting_id.empty(),
            "meeting id is not empty");

    int count = 0;

    for (const Participation& p : participations) {

        if (p.get_meeting() == meeting_id) {
            count++;
        }
    }

    ENSURE(count >= 0,
           "participant count is non-negative");

    return count;
}

//Overige functies

void Participation::print() {

    REQUIRE(!user.empty() && !meeting.empty(),
            "Participation attributes are not empty");

    std::cout << "PARTICIPATION: " << std::endl;

    std::cout << "User: " << user;
    std::cout << " | Meeting: " << meeting << std::endl;
}