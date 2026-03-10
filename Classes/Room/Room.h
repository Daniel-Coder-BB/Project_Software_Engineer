//
// Created by danny on 09-Mar-26.
//

#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
using namespace std;


class Room {
private:
    string name;
    string identifier;
    unsigned int capacity;

public:
    string get_name() const;

    void set_name(const string &name);

    string get_identifier() const;

    void set_identifier(const string &identifier);

    unsigned int get_capacity() const;

    void set_capacity(unsigned int capacity);

    void print();
};



#endif //ROOM_H
