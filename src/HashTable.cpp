#include "HashTable.h"
#include <cctype>

HashTable::HashTable() {
    // setting capacity to 150043 bc need a prime number roughly 1.5x the dataset size
    capacity = 150043;
    size = 0;
    table = new HashNode*[capacity];

    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}


HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;

            delete temp;
        }
    }
    
    delete[] table;
}


unsigned int HashTable::hash(const std::string& key) {
    unsigned long hValue = 0;

    // multiplying by a prime 31 helps spread out
    for (char c : key) {
        hValue = (hValue * 31) + std::tolower(c);
    }

    unsigned int idk = hValue % capacity;

    return idk;
}


void HashTable::insert(const Movie& movie) {
    unsigned int index = hash(movie.title);

    HashNode* newNode = new HashNode;
    newNode->movie = movie;
    newNode->next = nullptr;

    if (table[index] == nullptr) {
        table[index] = newNode;
    }
    else {
        newNode->next = table[index];
        table[index] = newNode;
    }

    size++;

    // lookup speeds will be o(n) if load factor over 0.75. resize to maintain O(1)
    if (static_cast<double>(size) / capacity > 0.75) {
        rehash();
    }
}


Movie* HashTable::search(const std::string& title) {
    unsigned int index = hash(title);
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->movie.title == title) {
            return &(current->movie);
        }

        current = current->next;
    }

    return nullptr;
}


void HashTable::rehash() {
    int oldCapacity = capacity;
    HashNode** oldTable = table;


    // scale to the next prime number
    capacity = 300007;
    table = new HashNode*[capacity];

    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }

    size = 0;

    // insert all existing nodes into the new table
    for (int i = 0; i < oldCapacity; i++) {
        HashNode* current = oldTable[i];

        while (current != nullptr) {
            insert(current->movie);
            HashNode* temp = current;
            current = current->next;

            delete temp;
        }
    }

    delete[] oldTable;
}