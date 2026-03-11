#ifndef ROOM_H
#define ROOM_H

/**
 * Korte beschrijving:
 * Deze klasse stelt onze Room voor.
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
