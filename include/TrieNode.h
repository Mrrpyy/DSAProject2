#pragma once

#include <vector>

#include "Movie.h"

struct TrieNode;

//custom linked list used for trie children
struct TrieChild {
    unsigned char character;

    TrieNode* node;

    TrieChild* next;

    TrieChild(
        unsigned char characterValue,
        TrieNode* childNode,
        TrieChild* nextChild = nullptr
    )
        : character(characterValue),
          node(childNode),
          next(nextChild) {}
};

//stores child links and matching movies
struct TrieNode {
    TrieChild* children = nullptr;

    std::vector<Movie> movies;
};
