//
// Created by danny on 10-Mar-26.
//

#ifndef MEETING_H
#define MEETING_H
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using Date = std::chrono::year_month_day;

class Meeting {
private:
    string label;
    string identifier;
    string room;
    Date data;

public:
    string get_label() const;

    void set_label(const string &label);

    string get_identifier() const;

    void set_identifier(const string &identifier);

    string get_room() const;

    void set_room(const string &room);
};



#endif //MEETING_H
