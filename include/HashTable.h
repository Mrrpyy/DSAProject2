#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "HashNode.h"
#include "Movie.h"

/**
 * Custom hash table for exact movie-title lookup.
 *
 * The table uses separate chaining for collisions and automatically grows
 * when the projected load factor would exceed 0.75.
 */
class HashTable {
public:
    // Creates an empty table with at least the requested number of buckets.
    explicit HashTable(std::size_t initialCapacity = 131071);

    // Deletes every chain node and releases the bucket array.
    ~HashTable();

    // Copying is disabled because this class owns raw dynamic memory.
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    // Adds one movie using its normalized title as the key.
    void insert(const Movie& movie);

    // Returns the first exact title match, or nullptr when no match exists.
    const Movie* search(const std::string& title) const;

    // Returns every exact match, including remakes with the same title.
    std::vector<Movie> searchAll(const std::string& title) const;

    // Statistics used by the benchmark and report.
    std::size_t getSize() const;
    std::size_t getCapacity() const;
    std::size_t getCollisionCount() const;

private:
    // Array of bucket heads. Each bucket is a singly linked list.
    HashNode** table;

    // Number of bucket positions currently allocated.
    std::size_t capacity;

    // Number of movie entries stored in the table.
    std::size_t size;

    // Number of insertions that entered a nonempty bucket.
    std::size_t collisionCount;

    // Helpers for selecting prime-number capacities.
    static bool isPrime(std::size_t number);
    static std::size_t nextPrime(std::size_t number);

    // Polynomial hash function for an already-normalized title.
    std::size_t hash(
        const std::string& normalizedKey,
        std::size_t modulus
    ) const;

    // Moves all existing nodes into a larger bucket array.
    void rehash(std::size_t newCapacity);
};
