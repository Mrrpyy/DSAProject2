#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "Movie.h"
#include "TrieNode.h"

//custom trie for exact search and autocomplete
class Trie {
public:
    Trie();

    ~Trie();

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    void insert(const Movie& movie);

    bool search(const std::string& title) const;

    std::vector<Movie> searchAll(const std::string& title) const;

    std::vector<Movie> autocomplete(
        const std::string& prefix,
        std::size_t maxResults = 10
    ) const;

private:
    TrieNode* root;

    static TrieNode* findChild(
        TrieNode* node,
        unsigned char character
    );

    static const TrieNode* findChild(
        const TrieNode* node,
        unsigned char character
    );

    static TrieNode* getOrCreateChild(
        TrieNode* node,
        unsigned char character
    );

    static void collectMovies(
        const TrieNode* node,
        std::vector<Movie>& results,
        std::size_t maxResults
    );

    static void deleteNodes(TrieNode* node);
};
