#include "Utilities.h"

#include <cctype>

std::string Utilities::normalizeTitle(const std::string& text) {
    std::string normalized;
    normalized.reserve(text.size());

    bool previousWasSpace = false;

    for (unsigned char character : text) {
        if (std::isspace(character)) {
            if (!normalized.empty() && !previousWasSpace) {
                normalized.push_back(' ');
            }
            previousWasSpace = true;
            continue;
        }

        previousWasSpace = false;

        // IMDb titles are UTF-8. Lowercase ASCII letters while preserving
        // non-ASCII bytes exactly as they appear.
        if (character >= 'A' && character <= 'Z') {
            normalized.push_back(static_cast<char>(character + ('a' - 'A')));
        } else {
            normalized.push_back(static_cast<char>(character));
        }
    }

    if (!normalized.empty() && normalized.back() == ' ') {
        normalized.pop_back();
    }

    return normalized;
}
