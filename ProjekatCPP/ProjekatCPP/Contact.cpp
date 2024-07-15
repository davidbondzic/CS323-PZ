#include "contact.h"
#include <iostream>

Contact::Contact(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber)
    : firstName(firstName), lastName(lastName), phoneNumber(phoneNumber) {}

std::string Contact::getFirstName() const {
    return firstName;
}

std::string Contact::getLastName() const {
    return lastName;
}

std::string Contact::getPhoneNumber() const {
    return phoneNumber;
}

void Contact::display() const {
    std::cout << "Ime: " << firstName << "\n";
    std::cout << "Prezime: " << lastName << "\n";
    std::cout << "Broj telefona: " << phoneNumber << "\n";
}