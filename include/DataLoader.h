#pragma once

#include <string>
#include <vector>

#include "Movie.h"

//loads and combines imdb movie data
class DataLoader {
public:
    std::vector<Movie> loadMovies(
        const std::string& basicsFile,
        const std::string& ratingsFile
    );

private:
    static std::vector<std::string> splitLine(
        const std::string& line,
        char delimiter
    );
};
