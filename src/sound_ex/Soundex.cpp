#include <sound_ex/Soundex.h>

#include <cctype>
#include <unordered_map>

namespace {

constexpr std::size_t MAX_CODE_LENGTH = 4;

const std::string INVALID_DIGIT = "*";

const std::unordered_map<char, std::string> ENCODINGS {
    {'b', "1"},
    {'f', "1"},
    {'p', "1"},
    {'v', "1"},

    {'c', "2"},
    {'g', "2"},
    {'j', "2"},
    {'k', "2"},
    {'q', "2"},
    {'s', "2"},
    {'x', "2"},
    {'z', "2"},

    {'d', "3"},
    {'t', "3"},

    {'l', "4"},

    {'m', "5"},
    {'n', "5"},

    {'r', "6"}
};

std::string upperFront(const std::string &word) {
    const auto c = static_cast<unsigned char>(word.front());
    return std::string(1, std::toupper(c));
}

char lower(char c) {
    return std::tolower(static_cast<unsigned char>(c));
}

std::string head(const std::string &word) {
    return word.substr(0, 1);
}

std::string tail(const std::string &word) {
    return word.substr(1);
}

bool isComplete(const std::string &encoding) {
    return encoding.length() == MAX_CODE_LENGTH;
}

std::string lastDigit(const std::string &encoding) {
    return encoding.empty() ? INVALID_DIGIT : std::string(1, encoding.back());
}

std::string zeroPad(const std::string &word) {
    const auto numZeros = MAX_CODE_LENGTH - word.length();
    return word + std::string(numZeros, '0');
}

} // namespace

std::string Soundex::encodedDigit(char c) const {
    const auto search = ENCODINGS.find(lower(c));
    return search == ENCODINGS.cend() ?  INVALID_DIGIT : search->second;
}

std::string Soundex::encodedDigits(const std::string &word) const {
    auto encoding = encodedDigit(word.front());

    for (auto c : tail(word)) {
        if (isComplete(encoding)) {
            break;
        }

        const auto digit = encodedDigit(c);
        if (digit != INVALID_DIGIT &&
            digit != lastDigit(encoding)) {
            encoding += digit;
        }
    }
    return encoding;
}

std::string Soundex::encode(const std::string &word) const {
    auto encoded = upperFront(head(word)) + tail(encodedDigits(word));
    return zeroPad(encoded);
}