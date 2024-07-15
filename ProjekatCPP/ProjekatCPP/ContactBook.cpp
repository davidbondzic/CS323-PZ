#include "contactbook.h"
#include <iostream>
#include <fstream>
#include <algorithm>

ContactBook::ContactBook() {
    contacts = readContactsFromFile();
}

void ContactBook::addContact(const Contact& contact) {
    contacts.push_back(contact);
    saveContactsToFile();
}

void ContactBook::deleteContact(const std::string& firstName, const std::string& lastName) {
    contacts.erase(std::remove_if(contacts.begin(), contacts.end(), [&](const Contact& contact) {
        return contact.getFirstName() == firstName && contact.getLastName() == lastName;
        }), contacts.end());
    saveContactsToFile();
}

void ContactBook::displayContacts() const {
    for (const auto& contact : contacts) {
        contact.display();
        std::cout << "-------------------\n";
    }
}

std::vector<Contact> ContactBook::readContactsFromFile() {
    std::vector<Contact> contacts;
    std::ifstream file(FILENAME);

    if (!file) {
        std::cerr << "Error " << FILENAME << std::endl;
        return contacts;
    }

    std::string firstName, lastName, phoneNumber;
    while (file >> firstName >> lastName >> phoneNumber) {
        contacts.emplace_back(firstName, lastName, phoneNumber);
    }

    file.close();
    return contacts;
}

void ContactBook::saveContactsToFile() const {
    std::ofstream file(FILENAME);

    if (!file) {
        std::cerr << "Error " << FILENAME << std::endl;
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.getFirstName() << " " << contact.getLastName() << " " << contact.getPhoneNumber() << "\n";
    }

    file.close();
}
