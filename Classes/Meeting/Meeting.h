#ifndef UITPROBEREN_MEETING_H
#define UITPROBEREN_MEETING_H

/*
 * Korte beschrijving:
 * Deze klasse stelt onze meeting voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok

#include <string>

//body-gedeelte
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

    friend bool operator==(const Meeting &lhs, const Meeting &rhs) {
        return lhs.label == rhs.label
               && lhs.identifier == rhs.identifier
               && lhs.room == rhs.room
               && lhs.date == rhs.date;
    }

    friend bool operator!=(const Meeting &lhs, const Meeting &rhs) {
        return !(lhs == rhs);
    }

    void print();
};


#endif //UITPROBEREN_MEETING_H