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
    std::vector<std::string> fields;
    std::stringstream stream(line);
    std::string field;

//split one tsv row into fields
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

//load movie details
    std::ifstream basics(basicsFile);

    if (!basics.is_open()) {
        std::cerr << "Could not open basics file: " << basicsFile << '\n';
        return movies;
    }

    std::string line;

    std::getline(basics, line);

    while (std::getline(basics, line)) {
        const std::vector<std::string> fields = splitLine(line, '\t');

//keep movie records with valid years
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
        }
    }

//match ratings to movies by imdb id
    std::unordered_map<std::string, std::size_t> indexById;
    indexById.reserve(movies.size());

    for (std::size_t i = 0; i < movies.size(); ++i) {
        indexById[movies[i].id] = i;
    }

    std::ifstream ratings(ratingsFile);

    if (!ratings.is_open()) {
        std::cerr << "Could not open ratings file: " << ratingsFile << '\n';
        return movies;
    }

    std::getline(ratings, line);

    while (std::getline(ratings, line)) {
        const std::vector<std::string> fields = splitLine(line, '\t');

        if (fields.size() < 3) {
            continue;
        }

        const auto match = indexById.find(fields[0]);
        if (match == indexById.end()) {
            continue;
        }

        try {
            Movie& movie = movies[match->second];
            movie.rating = std::stof(fields[1]);
            movie.numVotes = std::stoi(fields[2]);
        } catch (const std::exception&) {
        }
    }

    return movies;
}
