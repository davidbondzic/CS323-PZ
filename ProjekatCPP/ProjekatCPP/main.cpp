#include "contactbook.h"
#include "invalidphonenumberexception.h"
#include <iostream>
#include <regex>

bool isValidPhoneNumber(const std::string& phoneNumber) {
    std::regex phoneRegex(R"(\+?\d+(-\d+)*(\d+))");
    return std::regex_match(phoneNumber, phoneRegex);
}

int main() {
    ContactBook contactBook;

    while (true) {
        std::cout << "1. Dodaj kontakt\n";
        std::cout << "2. Obrisi kontakt\n";
        std::cout << "3. Prikazi sve kontakte\n";
        std::cout << "4. Izlaz\n";
        std::cout << "Izaberite opciju: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string firstName, lastName, phoneNumber;
            std::cout << "Unesite ime: ";
            std::getline(std::cin, firstName);
            std::cout << "Unesite prezime: ";
            std::getline(std::cin, lastName);
            std::cout << "Unesite broj telefona: ";
            std::getline(std::cin, phoneNumber);

            try {
                if (!isValidPhoneNumber(phoneNumber)) {
                    throw InvalidPhoneNumberException(phoneNumber);
                }

                Contact newContact(firstName, lastName, phoneNumber);
                contactBook.addContact(newContact);
            }
            catch (const InvalidPhoneNumberException& e) {
                std::cerr << "Greska: " << e.what() << std::endl;
            }
            break;
        }
        case 2: {
            std::string firstName, lastName;
            std::cout << "Unesite ime osobe koju zelite da obrisete: ";
            std::getline(std::cin, firstName);
            std::cout << "Unesite prezime osobe koju zelite da obrisete: ";
            std::getline(std::cin, lastName);

            contactBook.deleteContact(firstName, lastName);
            break;
        }
        case 3:
            contactBook.displayContacts();
            break;
        case 4:
            return 0;
        default:
            std::cout << "Nepostojeca opcija, izaberite ponovo.\n";
            break;
        }
    }
}
