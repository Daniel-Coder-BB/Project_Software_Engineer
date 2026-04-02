#ifndef PLANNING_SYSTEM_PROJECT_CAMPUS_H
#define PLANNING_SYSTEM_PROJECT_CAMPUS_H

/*
* Korte beschrijving:
 * Deze klasse stelt onze campus voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

// Include blok
#include <string>

class Campus {
private:
 std::string name;
 std::string identifier;

public:

     /*
     *This function gets the name attribute
     *@param None
     *@return the name of the campus
     *precondition name is not empty
     *postcondition returns this->name
     */
 [[nodiscard]] std::string get_name() const;

    /*
    *This function changes the name attribute
    *@param the name you want to change it to
    *@return None
    *precondition name is not empty
    *postcondition the input name is equal to of Campus
    */
 void set_name(const std::string &name);

     /*
     *This function gets the identifier attribute
     *@param None
     *@return the identifier of the Campus
     *precondition name is not empty
     *postcondition returns this->identifier
     */
 [[nodiscard]] std::string get_identifier() const;

    /*
    *This function changes the identifier attribute
    *@param the identifier you want to change it to
    *@return None
    *precondition identifier is not empty
    *postcondition the input identifier is equal to identifier of Campus
    */
 void set_identifier(const std::string &identifier);
};


#endif //PLANNING_SYSTEM_PROJECT_CAMPUS_H