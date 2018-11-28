#pragma once

#include <exception>
#include <string>

class BadFileAccess: public std::exception {
public:
    explicit BadFileAccess(std::string message);
    const char *what() const noexcept;

private:
    std::string message_;
};