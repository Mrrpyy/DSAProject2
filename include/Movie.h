#pragma once

#include <string>

//movie data loaded from imdb
struct Movie {
    std::string id;

    std::string title;

    int year = 0;

    float rating = 0.0F;

    int numVotes = 0;

    std::string genre;
};
