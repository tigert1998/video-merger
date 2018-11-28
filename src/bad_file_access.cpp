#include "bad_file_access.h"

BadFileAccess::BadFileAccess(std::string message): message_(message) {}

const char *BadFileAccess::what() const noexcept {
    return message_.data();
}