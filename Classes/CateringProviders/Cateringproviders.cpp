/*
* Korte beschrijving:
 * Deze klasse stelt onze Cateringproviders voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */

#include "Cateringproviders.h"
#include "Classes/DesignByContract/DesignByContract.h"

string Cateringproviders::get_campus() const {
 // ENSURE: returns this->campus
 return Campus;
}

void Cateringproviders::set_campus(const string &campus) {
 // REQUIRE: campus is not empty
 REQUIRE(!campus.empty(), "Precondition failure: campus cannot be empty");

 this->Campus = campus;

 // ENSURE: the input campus is equal to campus attribute
 ENSURE(this->Campus == campus, "Postcondition failure: campus not set correctly");
}

float Cateringproviders::get_co2() const {
 // ENSURE: returns this->co2
 return co2;
}

void Cateringproviders::set_co2(float co2) {
 // REQUIRE: co2 is bigger than 0
 // Merk op: De foutmelding "Value must be greater then zero" komt hier terecht.
 REQUIRE(co2 > 0.0, "Precondition failure: Value must be greater then zero");

 this->co2 = co2;

 // ENSURE: the input co2 is equal to co2 attribute
 ENSURE(this->co2 == co2, "Postcondition failure: co2 attribute not set correctly");
}