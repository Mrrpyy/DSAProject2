#include "Utilities.h"

#include <cctype>

std::string Utilities::normalizeTitle(const std::string& text) {
    std::string normalized;
    normalized.reserve(text.size());

    bool previousWasSpace = false;

    for (unsigned char character : text) {
//collapse repeated whitespace
        if (std::isspace(character)) {
            if (!normalized.empty() && !previousWasSpace) {
                normalized.push_back(' ');
            }

            previousWasSpace = true;
            continue;
        }

        previousWasSpace = false;

//lowercase ascii without changing utf eight bytes
        if (character >= 'A' && character <= 'Z') {
            normalized.push_back(
                static_cast<char>(character + ('a' - 'A'))
            );
        } else {
            normalized.push_back(static_cast<char>(character));
        }
    }

//remove a trailing space
    if (!normalized.empty() && normalized.back() == ' ') {
        normalized.pop_back();
    }

    return normalized;
}
