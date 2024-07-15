#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;

public:
    Contact(const std::string& firstName, const std::string& lastName, const std::string& phoneNumber);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;

    void display() const;
};

#endif
