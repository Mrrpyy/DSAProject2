#pragma once
#include <unordered_map>

#include "Movie.h"

struct TrieNode {
    bool isEndOfWord = false;
    std::unordered_map<char, TrieNode*> children;
    Movie movie;
};
