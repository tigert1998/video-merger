#pragma once

#include <iostream>

#define LOG_EXPR(x)\
    std::cout << #x << " = " << (x) << "\n"

constexpr const char *author_name = "tigertang";