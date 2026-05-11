#ifndef PARTICIPATION_H
#define PARTICIPATION_H

/**
 * Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 2.0
 */

#include <iostream>
#include <string>
#include <vector>

class Participation {
private:
    std::string user;
    std::string meeting;

public:

    /*
     *This function gets the user attribute
     *@param None
     *@return the user of the Participation object
     *precondition user is not empty
     *REQUIRE(!user.empty(), "user is not empty")
     *postcondition returns this->user
     * ENSURE(result == this->user, "returns this->user")
     */
    std::string get_user() const;

    /*
    *This function changes the user attribute
    *@param the user you want to change it to
    *@return None
    *precondition user is not empty
    *REQUIRE(!user.empty(), "user is not empty")
    *postcondition the input user is equal to user of Participation object
    *ENSURE(this->user == user, "the input user is equal to label user of Participation object")
    */
    void set_user(const std::string &user);

    /*
     *This function gets the meeting attribute
     *@param None
     *@return the meeting of the Participation object
     *precondition meeting is not empty
     *REQUIRE(!meeting.empty(), "meeting is not empty")
     *postcondition returns this->meeting
     *ENSURE(result == this->meeting, "returns this->meeting")
     */
    std::string get_meeting() const;

    /*
    *This function changes the meeting attribute
    *@param the meeting you want to change it to
    *@return None
    *precondition meeting is not empty
    *REQUIRE(!meeting.empty(), "meeting is not empty")
    *postcondition the input meeting is equal to meeting of Participation object
    *ENSURE(this->meeting == meeting, "the input meeting is equal to label meeting of Participation object")
    */
    void set_meeting(const std::string &meeting);

    friend bool operator==(const Participation &lhs, const Participation &rhs) {
        return lhs.user == rhs.user
               && lhs.meeting == rhs.meeting;
    }

    friend bool operator!=(const Participation &lhs, const Participation &rhs) {
        return !(lhs == rhs);
    }

    /*
    *This function counts the amount of participants
    *@param vector with participations and meeting id
    *@return amount of participants
    *precondition meeting id is not empty
    *REQUIRE(!meeting_id.empty(),
            "meeting id is not empty")
    *postcondition returns a non-negative integer
    *ENSURE(count >= 0,
           "participant count is non-negative")
    */
    static int countParticipants(
            const std::vector<Participation>& participations,
            const std::string& meeting_id);

    void print();
};

#endif //PARTICIPATION_H