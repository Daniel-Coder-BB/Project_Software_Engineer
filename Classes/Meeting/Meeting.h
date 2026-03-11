/**
 * Korte beschrijving:
 * Deze klasse stelt onze meeting voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
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

    void print();
};


#endif //UITPROBEREN_MEETING_H