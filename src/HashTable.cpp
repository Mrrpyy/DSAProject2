#include "HashTable.h"

#include <algorithm>

#include "Utilities.h"

HashTable::HashTable(std::size_t initialCapacity)
    : table(nullptr),
      capacity(nextPrime(std::max<std::size_t>(initialCapacity, 11))),
      size(0),
      collisionCount(0) {
    // Value-initialization sets every bucket pointer to nullptr.
    table = new HashNode*[capacity]{};
}

HashTable::~HashTable() {
    // Delete every linked-list node in every bucket.
    for (std::size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Release the dynamic bucket array after all chains are gone.
    delete[] table;
}

bool HashTable::isPrime(std::size_t number) {
    if (number < 2) {
        return false;
    }

    if (number % 2 == 0) {
        return number == 2;
    }

    // Check only odd divisors up to the square root of number.
    for (std::size_t divisor = 3;
         divisor <= number / divisor;
         divisor += 2) {
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

    // Every prime larger than two is odd.
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

    /**
     * Polynomial rolling hash.
     *
     * Multiplying the previous value by 131 makes character position matter,
     * while modulo keeps the intermediate value within the bucket range.
     */
    for (unsigned char character : normalizedKey) {
        hashValue = (hashValue * 131 + character) % modulus;
    }

    return hashValue;
}

void HashTable::insert(const Movie& movie) {
    const std::string key = Utilities::normalizeTitle(movie.title);

    // Empty normalized titles are not useful search keys.
    if (key.empty()) {
        return;
    }

    // Grow before insertion when the next item would exceed 75% capacity.
    const double projectedLoadFactor =
        static_cast<double>(size + 1) /
        static_cast<double>(capacity);

    if (projectedLoadFactor > 0.75) {
        rehash(nextPrime(capacity * 2));
    }

    const std::size_t index = hash(key, capacity);

    // A nonempty bucket means this insertion encountered a collision.
    if (table[index] != nullptr) {
        ++collisionCount;
    }

    // Insert at the front of the bucket chain in constant time.
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

    // Only the collision chain at the calculated bucket must be examined.
    while (current != nullptr) {
        if (current->key == key) {
            return &current->movie;
        }

        current = current->next;
    }

    return nullptr;
}

std::vector<Movie> HashTable::searchAll(
    const std::string& title
) const {
    std::vector<Movie> results;
    const std::string key = Utilities::normalizeTitle(title);

    if (key.empty()) {
        return results;
    }

    const std::size_t index = hash(key, capacity);
    const HashNode* current = table[index];

    // Continue through the full chain so duplicate titles are all returned.
    while (current != nullptr) {
        if (current->key == key) {
            results.push_back(current->movie);
        }

        current = current->next;
    }

    return results;
}

void HashTable::rehash(std::size_t newCapacity) {
    // Create a new empty bucket array with the larger capacity.
    HashNode** newTable = new HashNode*[newCapacity]{};
    std::size_t newCollisionCount = 0;

    // Move existing nodes directly instead of allocating replacement nodes.
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

    // Replace the old array after every node has been transferred.
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
