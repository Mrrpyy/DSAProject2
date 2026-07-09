#pragma once
#include <string>
#include "Movie.h"
#include "HashNode.h"


class HashTable {
public:
    HashTable();
    ~HashTable();
    void insert(const Movie& movie);
    Movie* search(const std::string& title);


private:
    HashNode** table;
    int capacity;
    int size;

    unsigned int hash(const std::string& key);
    void rehash();
};