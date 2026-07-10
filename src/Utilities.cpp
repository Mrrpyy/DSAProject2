#include "Utilities.h"

#include <cctype>

std::string Utilities::normalizeTitle(const std::string& text) {
    std::string normalized;
    normalized.reserve(text.size());

    bool previousWasSpace = false;

    for (unsigned char character : text) {
        // Treat every whitespace character as a regular space.
        if (std::isspace(character)) {
            // Avoid leading spaces and collapse consecutive spaces into one.
            if (!normalized.empty() && !previousWasSpace) {
                normalized.push_back(' ');
            }

            previousWasSpace = true;
            continue;
        }

        previousWasSpace = false;

        /**
         * IMDb titles are stored as UTF-8.
         *
         * Lowercase ASCII letters while preserving non-ASCII bytes exactly.
         * This gives reliable case-insensitive English title searches without
         * corrupting accented or non-Latin text.
         */
        if (character >= 'A' && character <= 'Z') {
            normalized.push_back(
                static_cast<char>(character + ('a' - 'A'))
            );
        } else {
            normalized.push_back(static_cast<char>(character));
        }
    }

    // Remove the one trailing space that may have been added during parsing.
    if (!normalized.empty() && normalized.back() == ' ') {
        normalized.pop_back();
    }

    return normalized;
}
