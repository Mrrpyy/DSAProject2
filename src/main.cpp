#include <iostream>
#include <vector>
#include <chrono>
#include "DataLoader.h"

int main() {
    std::cout << "Program started\n";
    std::cout << "Loading files...\n";

    DataLoader loader;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Movie> movies = loader.loadMovies(
        "../data/title.basics.tsv",
        "../data/title.ratings.tsv"
    );

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Loaded " << movies.size() << " movies.\n";
    std::cout << "Loading time: " << elapsed.count() << " seconds.\n";

    for (int i = 0; i < 10 && i < movies.size(); i++) {
        std::cout << movies[i].title
                  << " | " << movies[i].year
                  << " | Rating: " << movies[i].rating
                  << " | Votes: " << movies[i].numVotes
                  << " | " << movies[i].genre
                  << std::endl;
    }

    return 0;
}