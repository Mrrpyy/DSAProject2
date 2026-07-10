#pragma once

#include <vector>

#include "Movie.h"

//compares trie and hash table performance
class Benchmark {
public:
    void run(const std::vector<Movie>& movies) const;
};
