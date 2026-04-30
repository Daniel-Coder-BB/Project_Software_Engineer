#ifndef PLANNING_SYSTEM_PROJECT_CATERINGPROVIDERS_H
#define PLANNING_SYSTEM_PROJECT_CATERINGPROVIDERS_H

/*
* Korte beschrijving:
 * Deze klasse stelt onze Cateirngproviders voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

#include <iostream>
#include <string>
using namespace std;

class Cateringproviders {
private:
 string Campus;
 float co2;

public:
    /*
     *This function gets the campus attribute
     *@param None
     *@return the campus of the Cateringproviders object
     *precondition campus is not empty
     *postcondition returns this->campus
     */
 [[nodiscard]] string get_campus() const;

 /*
     *This function changes the campus attribute
     *@param campus the campus you want to change it to
     *@return None
     *precondition campus is not empty
     *postcondition the input campus is equal to campus attribute of Cateringproviders object
     */
 void set_campus(const string &campus);

    /*
     *This function gets the co2 attribute
     *@param None
     *@return the co2 of the Cateringprovider object
     *precondition co2 is not empty
     *postcondition returns this->co2
     */
 [[nodiscard]] float get_co2() const;

    /*
     *This function changes the co2 attribute
     *@param co2 the co2 you want to change it to
     *@return None
     *precondition co2 is not empty
     *precondition co2 is bigger then 0
     *postcondition the input co2 is equal to co2 attribute of Cateringprovider object
     */
 void set_co2(float co2);
};


#endif //PLANNING_SYSTEM_PROJECT_CATERINGPROVIDERS_H