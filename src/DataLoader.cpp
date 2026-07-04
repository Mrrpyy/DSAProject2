#include "DataLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

//Splits a line of text into fields using the given delimiter
std::vector<std::string> DataLoader::splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, delimiter)) {
        fields.push_back(field);
    }

    return fields;
}

std::vector<Movie> DataLoader::loadMovies(
    const std::string& basicsFile,
    const std::string& ratingsFile
) {
    std::vector<Movie> movies;

//Open the IMDb movie information file
    std::ifstream basics(basicsFile);

    if (!basics.is_open()) {
        std::cout << "Could not open basics file: " << basicsFile << std::endl;
        return movies;
    }

    std::string line;

//Skip the header row
    std::getline(basics, line);

//Read every movie entry in the file
    while (std::getline(basics, line)) {

        std::vector<std::string> fields = splitLine(line, '\t');

//Ignore malformed rows
        if (fields.size() < 9)
            continue;

        std::string id = fields[0];
        std::string titleType = fields[1];
        std::string title = fields[2];
        std::string yearString = fields[5];
        std::string genre = fields[8];

//Only keep actual movies
        if (titleType != "movie")
            continue;

//Skip movies with unknown release years
        if (yearString == "\\N")
            continue;

        Movie movie;

        movie.id = id;
        movie.title = title;
        movie.year = std::stoi(yearString);
        movie.genre = genre;

        movies.push_back(movie);
    }

    basics.close();

//Create a lookup table so ratings can be matched quickly by IMDb ID
    std::unordered_map<std::string, int> indexById;

    for (int i = 0; i < movies.size(); i++) {
        indexById[movies[i].id] = i;
    }

//Open the ratings dataset
    std::ifstream ratings(ratingsFile);

    if (!ratings.is_open()) {
        std::cout << "Could not open ratings file: " << ratingsFile << std::endl;
        return movies;
    }
//Skip the ratings header
    std::getline(ratings, line);

//Read every rating entry
    while (std::getline(ratings, line)) {

        std::vector<std::string> fields = splitLine(line, '\t');

//Ignore malformed rows
        if (fields.size() < 3)
            continue;

        std::string id = fields[0];

//Skip ratings for movies that werent loaded
        if (indexById.find(id) == indexById.end())
            continue;

        int movieIndex = indexById[id];

//Store the movies rating and vote count
        movies[movieIndex].rating = std::stof(fields[1]);
        movies[movieIndex].numVotes = std::stoi(fields[2]);
    }

    ratings.close();

    return movies;
}