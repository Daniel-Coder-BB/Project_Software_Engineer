//
// Created by danny on 10-Mar-26.
//

#ifndef PARTICIPATION_H
#define PARTICIPATION_H
#include <iostream>
#include <string>
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
