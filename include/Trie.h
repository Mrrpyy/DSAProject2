#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "Movie.h"
#include "TrieNode.h"

/**
 * Custom Trie that supports exact title search and prefix autocomplete.
 *
 * Titles are normalized, then stored one byte at a time. Shared prefixes use
 * the same nodes, while terminal nodes retain the complete Movie records.
 */
class Trie {
public:
    // Creates an empty root node.
    Trie();

    // Recursively releases every node and child-list entry.
    ~Trie();

    // Copying is disabled because this class owns raw dynamic memory.
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Inserts one movie into the character path for its normalized title.
    void insert(const Movie& movie);

    // Returns true when at least one movie has this exact normalized title.
    bool search(const std::string& title) const;

    // Returns all movies with this exact normalized title.
    std::vector<Movie> searchAll(const std::string& title) const;

    /**
     * Returns at most maxResults movies whose titles begin with prefix.
     */
    std::vector<Movie> autocomplete(
        const std::string& prefix,
        std::size_t maxResults = 10
    ) const;

private:
    // Starting point for every title path.
    TrieNode* root;

    // Finds an existing child edge with the requested character.
    static TrieNode* findChild(
        TrieNode* node,
        unsigned char character
    );

    // Const overload used by search functions.
    static const TrieNode* findChild(
        const TrieNode* node,
        unsigned char character
    );

    // Returns an existing child or creates one when it does not exist.
    static TrieNode* getOrCreateChild(
        TrieNode* node,
        unsigned char character
    );

    // Recursively gathers completed movies below a prefix node.
    static void collectMovies(
        const TrieNode* node,
        std::vector<Movie>& results,
        std::size_t maxResults
    );

    // Recursively deletes one node and all descendants.
    static void deleteNodes(TrieNode* node);
};
