#include "HashTable.h"

#include <algorithm>

#include "Utilities.h"

HashTable::HashTable(std::size_t initialCapacity)
    : table(nullptr),
      capacity(nextPrime(std::max<std::size_t>(initialCapacity, 11))),
      size(0),
      collisionCount(0) {
    table = new HashNode*[capacity]{};
}

HashTable::~HashTable() {
    for (std::size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    delete[] table;
}

bool HashTable::isPrime(std::size_t number) {
    if (number < 2) {
        return false;
    }
    if (number % 2 == 0) {
        return number == 2;
    }

    for (std::size_t divisor = 3; divisor <= number / divisor; divisor += 2) {
        if (number % divisor == 0) {
            return false;
        }
    }

    return true;
}

std::size_t HashTable::nextPrime(std::size_t number) {
    if (number <= 2) {
        return 2;
    }

    if (number % 2 == 0) {
        ++number;
    }

    while (!isPrime(number)) {
        number += 2;
    }

    return number;
}

std::size_t HashTable::hash(
    const std::string& normalizedKey,
    std::size_t modulus
) const {
    std::size_t hashValue = 0;

    for (unsigned char character : normalizedKey) {
        hashValue = (hashValue * 131 + character) % modulus;
    }

    return hashValue;
}

void HashTable::insert(const Movie& movie) {
    const std::string key = Utilities::normalizeTitle(movie.title);
    if (key.empty()) {
        return;
    }

    const double projectedLoadFactor =
        static_cast<double>(size + 1) / static_cast<double>(capacity);

    if (projectedLoadFactor > 0.75) {
        rehash(nextPrime(capacity * 2));
    }

    const std::size_t index = hash(key, capacity);

    if (table[index] != nullptr) {
        ++collisionCount;
    }

    HashNode* newNode = new HashNode;
    newNode->key = key;
    newNode->movie = movie;
    newNode->next = table[index];
    table[index] = newNode;
    ++size;
}

const Movie* HashTable::search(const std::string& title) const {
    const std::string key = Utilities::normalizeTitle(title);
    if (key.empty()) {
        return nullptr;
    }

    const std::size_t index = hash(key, capacity);
    const HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            return &current->movie;
        }
        current = current->next;
    }

    return nullptr;
}

std::vector<Movie> HashTable::searchAll(const std::string& title) const {
    std::vector<Movie> results;
    const std::string key = Utilities::normalizeTitle(title);

    if (key.empty()) {
        return results;
    }

    const std::size_t index = hash(key, capacity);
    const HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            results.push_back(current->movie);
        }
        current = current->next;
    }

    return results;
}

void HashTable::rehash(std::size_t newCapacity) {
    HashNode** newTable = new HashNode*[newCapacity]{};
    std::size_t newCollisionCount = 0;

    for (std::size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* nextNode = current->next;
            const std::size_t newIndex = hash(current->key, newCapacity);

            if (newTable[newIndex] != nullptr) {
                ++newCollisionCount;
            }

            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            current = nextNode;
        }
    }

    delete[] table;
    table = newTable;
    capacity = newCapacity;
    collisionCount = newCollisionCount;
}

std::size_t HashTable::getSize() const {
    return size;
}

std::size_t HashTable::getCapacity() const {
    return capacity;
}

std::size_t HashTable::getCollisionCount() const {
    return collisionCount;
}
