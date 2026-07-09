#include "Trie.h"

Trie::Trie() : root(new TrieNode) {}

Trie::~Trie() {
    deleteNodes(root);
}

void Trie::insert(const Movie& movie) {
    if (movie.title.empty()) {
        return;
    }

    TrieNode* current = root;
    for (char character : movie.title) {
        if (current->children.find(character) == current->children.end()) {
            current->children[character] = new TrieNode;
        }

        current = current->children[character];
    }

    current->isEndOfWord = true;
    current->movie = movie;
}

bool Trie::search(const std::string& title) const {
    const TrieNode* current = root;

    for (char character : title) {
        auto child = current->children.find(character);

        if (child == current->children.end()) {
            return false;
        }

        current = child->second;
    }

    return current->isEndOfWord;
}

std::vector<Movie> Trie::autocomplete(const std::string& prefix) const {
    const TrieNode* current = root;

    for (char character : prefix) {
        auto child = current->children.find(character);

        if (child == current->children.end()) {
            return {};
        }

        current = child->second;
    }

    std::vector<Movie> results;
    collectMovies(current, results);
    return results;
}

void Trie::collectMovies(const TrieNode* node, std::vector<Movie>& results) const {
    if (node->isEndOfWord) {
        results.push_back(node->movie);
    }

    for (auto child : node->children) {
        collectMovies(child.second, results);
    }
}

// Deletes every node created by the Trie to free allocated memory.
void Trie::deleteNodes(TrieNode* node) {
    if (node == nullptr) {
        return;
    }

    for (auto child : node->children) {
        deleteNodes(child.second);
    }

    delete node;
}
