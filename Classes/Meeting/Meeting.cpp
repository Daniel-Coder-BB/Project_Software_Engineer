/**
* Korte beschrijving:
* Deze klasse stelt onze Meeting voor.
*
* @authors Bruno Luango en Ibrahim Akiyev
* @date 11/03/2026
* @version 1.1
*/

#include "Meeting.h"
#include "Classes/DesignByContract/DesignByContract.h"
#include <iostream>



std::string Meeting::get_label() const {
    REQUIRE(!label.empty(), "label is not empty");
    std::string result = label;
    ENSURE(result == this->label, "returns this->label");
    return result;
}

std::string Meeting::get_identifier() const {
    REQUIRE(!identifier.empty(), "identifier is not empty");
    std::string result = identifier;
    ENSURE(result == this->identifier, "returns this->identifier");
    return result;
}

std::string Meeting::get_room() const {
    REQUIRE(online || !room.empty(), "room must be set if meeting is not online");

    if (online) {
        return "ONLINE";
    }

    std::string result = room;
    ENSURE(result == this->room, "returns this->room");
    return result;
}


std::string Meeting::get_date() const {
    REQUIRE(!date.empty(), "date is not empty");
    std::string result = date;
    ENSURE(result == this->date, "returns this->date");
    return result;
}

int Meeting::get_hour() const {
    ENSURE(hour >= 0 && hour <= 23, "hour is within valid range");
    return hour;
}

bool Meeting::is_online() const {
    ENSURE(online == true || online == false, "online is a valid boolean");
    return online;
}

bool Meeting::is_catering() const {
    ENSURE(catering == true || catering == false, "catering is a valid boolean");
    return catering;
}

double Meeting::get_co2() const {
    ENSURE(co2_emission >= 0, "co2 emission is non-negative");
    return co2_emission;
}



void Meeting::set_label(const std::string &label) {
    REQUIRE(!label.empty(), "label is not empty");
    this->label = label;
    ENSURE(this->label == label, "label correctly set");
}

void Meeting::set_identifier(const std::string &identifier) {
    REQUIRE(!identifier.empty(), "identifier is not empty");
    this->identifier = identifier;
    ENSURE(this->identifier == identifier, "identifier correctly set");
}

void Meeting::set_room(const std::string &room) {
    REQUIRE(!room.empty(), "room is not empty");
    this->room = room;
    ENSURE(this->room == room, "room correctly set");
}

void Meeting::set_date(const std::string &date) {
    REQUIRE(!date.empty(), "date is not empty");
    this->date = date;
    ENSURE(this->date == date, "date correctly set");
}

void Meeting::set_hour(int hour) {
    REQUIRE(hour >= 0 && hour <= 23, "hour must be between 0 and 23");
    this->hour = hour;
    ENSURE(this->hour == hour, "hour correctly set");
}

void Meeting::set_online(bool online) {
    this->online = online;
    ENSURE(this->online == online, "online status correctly set");
}

void Meeting::set_catering(bool catering) {
    this->catering = catering;
    ENSURE(this->catering == catering, "catering status correctly set");
}


void Meeting::print() {
    REQUIRE(!label.empty() && !identifier.empty() && !room.empty() && !date.empty(),
            "Meeting attributes are not empty");

    std::cout << "MEETING" << std::endl;
    std::cout << "Label: " << label;
    std::cout << " | Identifier: " << identifier;
    std::cout << " | Room: " << room;
    std::cout << " | Date: " << date << std::endl;

    ENSURE(!label.empty(), "label still intact after print");
}
