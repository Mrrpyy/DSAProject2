#include "DataLoader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::vector<std::string> DataLoader::splitLine(
    const std::string& line,
    char delimiter
) {
    // Store every field extracted from the current TSV row.
    std::vector<std::string> fields;
    std::stringstream stream(line);
    std::string field;

    // Read characters until a tab is reached, then save the completed field.
    while (std::getline(stream, field, delimiter)) {
        fields.push_back(field);
    }

    return fields;
}

std::vector<Movie> DataLoader::loadMovies(
    const std::string& basicsFile,
    const std::string& ratingsFile
) {
    std::vector<Movie> movies;

    // title.basics.tsv supplies IDs, types, titles, years, and genres.
    std::ifstream basics(basicsFile);

    if (!basics.is_open()) {
        std::cerr << "Could not open basics file: " << basicsFile << '\n';
        return movies;
    }

    std::string line;

    // The first line is a header containing column names.
    std::getline(basics, line);

    // Read one row at a time so the very large file is not copied into memory.
    while (std::getline(basics, line)) {
        const std::vector<std::string> fields = splitLine(line, '\t');

        // title.basics.tsv needs at least nine columns for the fields we use.
        // Keep only real movies and skip rows whose release year is unknown.
        if (fields.size() < 9 ||
            fields[1] != "movie" ||
            fields[5] == "\\N") {
            continue;
        }

        try {
            Movie movie;
            movie.id = fields[0];
            movie.title = fields[2];
            movie.year = std::stoi(fields[5]);
            movie.genre = fields[8];
            movies.push_back(movie);
        } catch (const std::exception&) {
            // Skip malformed rows instead of ending the entire import.
        }
    }

    /**
     * Map each IMDb ID to its position in the movie vector.
     *
     * This temporary standard-library map is used only to merge files. It is
     * not one of the two custom data structures evaluated by the project.
     */
    std::unordered_map<std::string, std::size_t> indexById;
    indexById.reserve(movies.size());

    for (std::size_t i = 0; i < movies.size(); ++i) {
        indexById[movies[i].id] = i;
    }

    // title.ratings.tsv supplies average ratings and vote counts.
    std::ifstream ratings(ratingsFile);

    if (!ratings.is_open()) {
        std::cerr << "Could not open ratings file: " << ratingsFile << '\n';
        return movies;
    }

    // Skip the ratings header.
    std::getline(ratings, line);

    while (std::getline(ratings, line)) {
        const std::vector<std::string> fields = splitLine(line, '\t');

        if (fields.size() < 3) {
            continue;
        }

        // Match the ratings row to the movie with the same IMDb ID.
        const auto match = indexById.find(fields[0]);
        if (match == indexById.end()) {
            continue;
        }

        try {
            Movie& movie = movies[match->second];
            movie.rating = std::stof(fields[1]);
            movie.numVotes = std::stoi(fields[2]);
        } catch (const std::exception&) {
            // Preserve the Movie defaults when rating values are malformed.
        }
    }

    return movies;
}
