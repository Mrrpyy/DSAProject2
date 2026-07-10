#include "Menu.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

Menu::Menu(const std::vector<Movie>& movieData) : movies(movieData) {
    buildStructures();
}

void Menu::buildStructures() {
    std::cout << "Building Trie and Hash Table...\n";

    for (const Movie& movie : movies) {
        trie.insert(movie);
        hashTable.insert(movie);
    }

    std::cout << "Search structures ready.\n";
}

void Menu::run() {
    while (true) {
        std::cout << "\n========== MOVIE SEARCH ENGINE ==========\n"
                  << "1. Search for an exact movie title\n"
                  << "2. Autocomplete a movie title\n"
                  << "3. Run Trie vs Hash Table benchmark\n"
                  << "4. Exit\n"
                  << "Choose an option: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            searchMovie();
        } else if (choice == "2") {
            autocompleteMovie();
        } else if (choice == "3") {
            compareStructures();
        } else if (choice == "4") {
            std::cout << "Goodbye.\n";
            return;
        } else {
            std::cout << "Invalid choice. Enter 1, 2, 3, or 4.\n";
        }
    }
}

void Menu::searchMovie() const {
    using Clock = std::chrono::steady_clock;

    std::cout << "Enter the complete movie title: ";
    std::string title;
    std::getline(std::cin, title);

    const auto trieStart = Clock::now();
    const std::vector<Movie> trieResults = trie.searchAll(title);
    const auto trieEnd = Clock::now();

    const auto hashStart = Clock::now();
    const std::vector<Movie> hashResults = hashTable.searchAll(title);
    const auto hashEnd = Clock::now();

    const double trieMicroseconds =
        std::chrono::duration<double, std::micro>(trieEnd - trieStart).count();
    const double hashMicroseconds =
        std::chrono::duration<double, std::micro>(hashEnd - hashStart).count();

    if (trieResults.empty()) {
        std::cout << "No matching movie was found.\n";
    } else {
        std::cout << "\nMatches:\n";
        for (const Movie& movie : trieResults) {
            printMovie(movie);
        }
    }

    std::cout << std::fixed << std::setprecision(3)
              << "Trie exact search: " << trieMicroseconds << " us\n"
              << "Hash Table exact search: " << hashMicroseconds << " us\n"
              << "Trie matches: " << trieResults.size()
              << ", Hash Table matches: " << hashResults.size() << '\n';
}

void Menu::autocompleteMovie() const {
    std::cout << "Enter the beginning of a movie title: ";
    std::string prefix;
    std::getline(std::cin, prefix);

    const std::vector<Movie> results = trie.autocomplete(prefix, 10);

    if (results.empty()) {
        std::cout << "No autocomplete suggestions were found.\n";
        return;
    }

    std::cout << "\nSuggestions (maximum 10):\n";
    for (const Movie& movie : results) {
        printMovie(movie);
    }
}

void Menu::compareStructures() const {
    benchmark.run(movies);
}

void Menu::printMovie(const Movie& movie) {
    std::cout << "- " << movie.title << " (" << movie.year << ")"
              << " | Rating: " << movie.rating
              << " | Votes: " << movie.numVotes
              << " | Genres: " << movie.genre << '\n';
}
