#pragma once
#include <string>
#include <vector>
#include "Movie.h"
#include "TrieNode.h"

class Trie {
public:
    Trie();
    ~Trie();

    void insert(const Movie& movie);
    bool search(const std::string& title) const;
    std::vector<Movie> autocomplete(const std::string& prefix) const;

private:
    TrieNode* root;

    void collectMovies(const TrieNode* node, std::vector<Movie>& results) const;
    static void deleteNodes(TrieNode* node);
};
