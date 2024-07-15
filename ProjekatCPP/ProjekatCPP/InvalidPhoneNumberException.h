#ifndef INVALIDPHONENUMBEREXCEPTION_H
#define INVALIDPHONENUMBEREXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidPhoneNumberException : public std::runtime_error {
public:
    explicit InvalidPhoneNumberException(const std::string& message)
        : std::runtime_error("Neispravan unos broja: " + message) {}
};

#endif
