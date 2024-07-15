#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include "contact.h"
#include <vector>

class ContactBook {
private:
    std::vector<Contact> contacts;
    const std::string FILENAME = "contacts.txt";

public:
    ContactBook();

    void addContact(const Contact& contact);
    void deleteContact(const std::string& firstName, const std::string& lastName);
    void displayContacts() const;

private:
    std::vector<Contact> readContactsFromFile();
    void saveContactsToFile() const;
};

#endif
