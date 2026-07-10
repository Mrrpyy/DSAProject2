#pragma once

#include <vector>

#include "Movie.h"

/**
 * Measures the build and query performance of the custom Trie and HashTable.
 */
class Benchmark {
public:
    // Runs all benchmark tests on the same movie dataset and prints results.
    void run(const std::vector<Movie>& movies) const;
};
