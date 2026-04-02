#ifndef PLANNING_SYSTEM_PROJECT_BUILDINGS_H
#define PLANNING_SYSTEM_PROJECT_BUILDINGS_H

/*
 * Korte beschrijving:
 * Deze klasse stelt onze buildings voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

// Include blok
#include <string>


class Buildings {
private:
    std::string name;
    std::string identifier;
    std::string campus;

public:

    /*
     *This function gets the name attribute
     *@param None
     *@return the name of the Buildings
     *precondition name is not empty
     *postcondition returns this->name
     */
    [[nodiscard]] std::string get_name() const;

    /*
    *This function changes the name attribute
    *@param the name you want to change it to
    *@return None
    *precondition name is not empty
    *postcondition the input name is equal to name of Buildings
    */
    void set_name(const std::string &name);

    /*
     *This function gets the identifier attribute
     *@param None
     *@return the identifier of the Buildings
     *precondition identifier is not empty
     *postcondition returns this->identifier
     */
    [[nodiscard]] std::string get_identifier() const;

    /*
    *This function changes the identifier attribute
    *@param the identifier you want to change it to
    *@return None
    *precondition identifier is not empty
    *postcondition the input identifier is equal to identifier of Buuldings
    */
    void set_identifier(const std::string &identifier);

    /*
     *This function gets the campus attribute
     *@param None
     *@return the campus of the Buildings
     *precondition campus is not empty
     *postcondition returns this->campus
     */
    [[nodiscard]] std::string get_campus() const;

    /*
    *This function changes the campus attribute
    *@param the campus you want to change it to
    *@return None
    *precondition campus is not empty
    *postcondition the input campus is equal to campus of Buuldings
    */
    void set_campus(const std::string &campus);
};


#endif //PLANNING_SYSTEM_PROJECT_BUILDINGS_H