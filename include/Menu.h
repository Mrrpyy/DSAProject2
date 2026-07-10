#pragma once

#include <vector>

#include "Benchmark.h"
#include "HashTable.h"
#include "Movie.h"
#include "Trie.h"

//handles the console menu
class Menu {
public:
    explicit Menu(const std::vector<Movie>& movies);

    void run();

private:
    const std::vector<Movie>& movies;

    Trie trie;
    HashTable hashTable;
    Benchmark benchmark;

    void buildStructures();

    void searchMovie() const;

    void autocompleteMovie() const;

    void compareStructures() const;

    static void printMovie(const Movie& movie);
};
