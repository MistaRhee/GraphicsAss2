#pragma once

#include <string>
#include <exception>

struct mException : public std::exception {
    const char* what() const throw() {
        return message.c_str();
    }
    mException(std::string in) {
        message = in;
    }
    std::string message;
};