#pragma once
#include <string>
#include "Movie.h"
class HashTable{public: HashTable(); void insert(const Movie&); Movie* search(const std::string&); private: unsigned int hash(const std::string&);};
