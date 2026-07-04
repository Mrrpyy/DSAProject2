#pragma once

#include <string>
#include <vector>

#include "Movie.h"
//DataLoader is responsible for reading the IMDb datasets and converting them into a vector of Movie objects

class DataLoader {

public:
//Reads the IMDb basics and ratings datasets combines the information and returns all movies

    std::vector<Movie> loadMovies(
        const std::string& basicsFile,
        const std::string& ratingsFile
    );

private:
//Splits a line of text using the specified delimiter parsing TSV files
    std::vector<std::string> splitLine(
        const std::string& line,
        char delimiter
    );
};