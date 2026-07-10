#include "Trie.h"

#include "Utilities.h"

Trie::Trie()
    : root(new TrieNode) {
}

Trie::~Trie() {
    deleteNodes(root);
}

TrieNode* Trie::findChild(
    TrieNode* node,
    unsigned char character
) {
    TrieChild* current = node->children;

//find a child in the custom linked list
    while (current != nullptr) {
        if (current->character == character) {
            return current->node;
        }

        current = current->next;
    }

    return nullptr;
}

const TrieNode* Trie::findChild(
    const TrieNode* node,
    unsigned char character
) {
    const TrieChild* current = node->children;

    while (current != nullptr) {
        if (current->character == character) {
            return current->node;
        }

        current = current->next;
    }

    return nullptr;
}

TrieNode* Trie::getOrCreateChild(
    TrieNode* node,
    unsigned char character
) {
    TrieNode* existing = findChild(node, character);
    if (existing != nullptr) {
        return existing;
    }

//create a child when the path is missing
    TrieNode* newNode = new TrieNode;
    node->children = new TrieChild(
        character,
        newNode,
        node->children
    );

    return newNode;
}

void Trie::insert(const Movie& movie) {
    const std::string key = Utilities::normalizeTitle(movie.title);

    if (key.empty()) {
        return;
    }

    TrieNode* current = root;

//store the normalized title one character at a time
    for (unsigned char character : key) {
        current = getOrCreateChild(current, character);
    }

//keep every movie that shares the same title
    current->movies.push_back(movie);
}

bool Trie::search(const std::string& title) const {
    return !searchAll(title).empty();
}

std::vector<Movie> Trie::searchAll(
    const std::string& title
) const {
    const std::string key = Utilities::normalizeTitle(title);

    if (key.empty()) {
        return {};
    }

    const TrieNode* current = root;

    for (unsigned char character : key) {
        current = findChild(current, character);

        if (current == nullptr) {
            return {};
        }
    }

    return current->movies;
}

std::vector<Movie> Trie::autocomplete(
    const std::string& prefix,
    std::size_t maxResults
) const {
    if (maxResults == 0) {
        return {};
    }

    const std::string key = Utilities::normalizeTitle(prefix);
    const TrieNode* current = root;

    for (unsigned char character : key) {
        current = findChild(current, character);

        if (current == nullptr) {
            return {};
        }
    }

    std::vector<Movie> results;
    results.reserve(maxResults);
//collect up to the requested number of matches
    collectMovies(current, results, maxResults);
    return results;
}

void Trie::collectMovies(
    const TrieNode* node,
    std::vector<Movie>& results,
    std::size_t maxResults
) {
    if (node == nullptr || results.size() >= maxResults) {
        return;
    }

    for (const Movie& movie : node->movies) {
        if (results.size() >= maxResults) {
            return;
        }

        results.push_back(movie);
    }

    const TrieChild* child = node->children;

    while (child != nullptr && results.size() < maxResults) {
        collectMovies(child->node, results, maxResults);
        child = child->next;
    }
}

void Trie::deleteNodes(TrieNode* node) {
    if (node == nullptr) {
        return;
    }

//delete children before the parent
    TrieChild* child = node->children;

    while (child != nullptr) {
        TrieChild* nextChild = child->next;
        deleteNodes(child->node);
        delete child;
        child = nextChild;
    }

    delete node;
}
