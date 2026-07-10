#pragma once

#include <string>

#include "Movie.h"

//node used for separate chaining
struct HashNode {
    std::string key;

    Movie movie;

    HashNode* next = nullptr;
};
