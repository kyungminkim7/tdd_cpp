#pragma once

#include <string>

class Soundex {
public:
    std::string encodedDigit(char c) const;
    std::string encode(const std::string &word) const;

private:
    std::string encodedDigits(const std::string &word) const;
};