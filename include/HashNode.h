#pragma once

#include <string>

#include "Movie.h"

/**
 * One entry in a HashTable bucket's linked list.
 *
 * Separate chaining allows several entries to occupy the same bucket when
 * their keys produce the same hash-table index.
 */
struct HashNode {
    // Normalized title used as the hash-table key.
    std::string key;

    // Complete movie record stored by this node.
    Movie movie;

    // Next collision-chain node, or nullptr at the end of the chain.
    HashNode* next = nullptr;
};
