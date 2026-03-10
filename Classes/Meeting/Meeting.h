//
// Created by ibrab on 10.03.2026.
//

#ifndef UITPROBEREN_MEETING_H
#define UITPROBEREN_MEETING_H
#include <string>
#include <ctime>


class Meeting {
private:
    std::string label;
    std::string identifier;
    std::string room;
    tm data;

public:
    std::string get_label() const {
        return label;
    }

    void set_label(const std::string &new_label) {
        this->label = new_label;
    }

    std::string get_identifier() const {
        return identifier;
    }

    void set_identifier(const std::string &new_identifier) {
        this->identifier = identifier;
    }

    std::string get_room() const {
        return room;
    }

    void set_room(const std::string &new_room) {
        this->room = new_room;
    }

    tm get_data() const {
        return data;
    }

    void set_data(const tm &data) {
        this->data = data;
    }
};


#endif //UITPROBEREN_MEETING_H