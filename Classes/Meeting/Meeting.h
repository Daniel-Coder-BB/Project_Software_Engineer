//
// Created by ibrab on 10.03.2026.
//

#ifndef UITPROBEREN_MEETING_H
#define UITPROBEREN_MEETING_H
#include <string>


class Meeting {
private:
    std::string label;
    std::string identifier;
    std::string room;
    std::string date;

public:
    [[nodiscard]] std::string get_label() const;

    void set_label(const std::string &label);

    [[nodiscard]] std::string get_identifier() const;

    void set_identifier(const std::string &identifier);

    [[nodiscard]] std::string get_room() const;

    void set_room(const std::string &room);

    [[nodiscard]] std::string get_date() const;

    void set_date(const std::string &date);
};


#endif //UITPROBEREN_MEETING_H