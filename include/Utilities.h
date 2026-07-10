#pragma once

#include <string>

/**
 * Shared helper functions used by both search structures.
 */
class Utilities {
public:
    /**
     * Normalizes user input and stored titles for consistent comparisons.
     *
     * The function converts ASCII letters to lowercase, collapses repeated
     * whitespace, and removes leading or trailing whitespace.
     */
    static std::string normalizeTitle(const std::string& text);
};
