#ifndef PARTICIPATION_H
#define PARTICIPATION_H

/**
 * Korte beschrijving:
 * Deze klasse stelt onze Participation voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
#include <iostream>
#include <string>

// Globale using statements
using namespace std;


class Participation {
private:
    string user;
    string meeting;
public:
    string get_user() const;

    void set_user(const string &user);

    string get_meeting() const;

    void set_meeting(const string &meeting);

    void print();
};



#endif //PARTICIPATION_H
