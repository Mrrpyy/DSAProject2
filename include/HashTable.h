#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "HashNode.h"
#include "Movie.h"

//custom hash table for exact title searches
class HashTable {
public:
    explicit HashTable(std::size_t initialCapacity = 131071);

    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void insert(const Movie& movie);

    const Movie* search(const std::string& title) const;

    std::vector<Movie> searchAll(const std::string& title) const;

    std::size_t getSize() const;
    std::size_t getCapacity() const;
    std::size_t getCollisionCount() const;

private:
    HashNode** table;

    std::size_t capacity;

    std::size_t size;

    std::size_t collisionCount;

    static bool isPrime(std::size_t number);
    static std::size_t nextPrime(std::size_t number);

    std::size_t hash(
        const std::string& normalizedKey,
        std::size_t modulus
    ) const;

    void rehash(std::size_t newCapacity);
};
