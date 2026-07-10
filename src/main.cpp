#include <chrono>
#include <filesystem>
#include <iostream>
#include <vector>

#include "DataLoader.h"
#include "Menu.h"

int main() {
    namespace fs = std::filesystem;

//support running from the project root or clion build folder
    fs::path dataDirectory = "data";

    if (!fs::exists(dataDirectory / "title.basics.tsv")) {
        dataDirectory = "../data";
    }

    const fs::path basicsPath =
        dataDirectory / "title.basics.tsv";
    const fs::path ratingsPath =
        dataDirectory / "title.ratings.tsv";

//stop when the dataset files are missing
    if (!fs::exists(basicsPath) || !fs::exists(ratingsPath)) {
        std::cerr
            << "IMDb files were not found.\n"
            << "Place title.basics.tsv and title.ratings.tsv "
            << "in the data folder.\n";
        return 1;
    }

    std::cout << "Loading IMDb data...\n";

    DataLoader loader;
    const auto start = std::chrono::steady_clock::now();

    std::vector<Movie> movies = loader.loadMovies(
        basicsPath.string(),
        ratingsPath.string()
    );

    const auto end = std::chrono::steady_clock::now();

    if (movies.empty()) {
        std::cerr << "No movies were loaded.\n";
        return 1;
    }

//use one hundred thousand movies for the assignment requirement
    constexpr std::size_t datasetLimit = 100000;

    if (movies.size() > datasetLimit) {
        movies.resize(datasetLimit);
    }

    const double loadingSeconds =
        std::chrono::duration<double>(end - start).count();

    std::cout << "Loaded " << movies.size()
              << " movies in " << loadingSeconds
              << " seconds.\n";

//start the interactive menu
    Menu menu(movies);
    menu.run();

    return 0;
}
