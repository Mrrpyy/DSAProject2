#pragma once
#include <string>

//Represents a single movie loaded from the IMDb datasets each Movie object contains basic information and rating data

struct Movie {
//Unique IMDb identifier (tt0111161)
    std::string id;
//Movie title
    std::string title;
//Release year
    int year = 0;
//IMDb average rating
    float rating = 0.0f;
//Total number of IMDb user votes
    int numVotes = 0;
//Movie genres
    std::string genre;
};