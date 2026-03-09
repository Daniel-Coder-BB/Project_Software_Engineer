//
// Created by danny on 05-Mar-26.
//

#ifndef CD_H
#define CD_H
#include <string>
#include <iostream>
using namespace std;

class CD {
private:
    string room;
    string identifier;
    int capacity;
    float price;

public:
    void setartist(const string &artist) {
        this->room = artist;
    }

    void settitle(const string &title) {
        this->identifier = title;
    }

    void setyear(int year) {
        this->capacity = year;
    }



    void print() const {
        std::cout << "Room: " << room << " | Identifier: " << identifier
                  << " | Capacity: " << capacity << std::endl;
    }
};



#endif //CD_H
