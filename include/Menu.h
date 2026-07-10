#pragma once

#include <vector>

#include "Benchmark.h"
#include "HashTable.h"
#include "Movie.h"
#include "Trie.h"

/**
 * Controls the interactive console interface.
 *
 * The constructor builds both custom data structures from the supplied movie
 * vector. run() then lets users search, autocomplete, benchmark, or exit.
 */
class Menu {
public:
    // Stores a reference to the loaded data and builds both search structures.
    explicit Menu(const std::vector<Movie>& movies);

    // Repeatedly displays the menu until the user selects Exit.
    void run();

private:
    // Original dataset used by the benchmark.
    const std::vector<Movie>& movies;

    // Search structures compared by the project.
    Trie trie;
    HashTable hashTable;
    Benchmark benchmark;

    // Inserts every movie into both structures once at program startup.
    void buildStructures();

    // Handles one exact-title search request.
    void searchMovie() const;

    // Handles one prefix-autocomplete request.
    void autocompleteMovie() const;

    // Runs the complete performance comparison.
    void compareStructures() const;

    // Prints one movie in a consistent, readable format.
    static void printMovie(const Movie& movie);
};
