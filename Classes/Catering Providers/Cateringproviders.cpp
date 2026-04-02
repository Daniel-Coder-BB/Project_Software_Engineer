/*
* Korte beschrijving:
 * Deze klasse stelt onze Cateirngproviders voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 02/04/2026
 * @version 2.0
 */
#include "Cateringproviders.h"

string Cateringproviders::get_campus() const {
 return Campus;
}

void Cateringproviders::set_campus(const string &campus) {
 Campus = campus;
}

float Cateringproviders::get_co2() const {
 return co2;
}

void Cateringproviders::set_co2(float co2) {
 if (co2 <=0.0) {
  throw std::invalid_argument("Value must be greater then zero");
 }
 this->co2 = co2;
}
