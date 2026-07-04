#pragma once
#include <string>
#include <vector>
#include "Movie.h"
#include "TrieNode.h"
class Trie{public: Trie(); void insert(const Movie&); bool search(const std::string&); std::vector<Movie> autocomplete(const std::string&); private: TrieNode* root;};
