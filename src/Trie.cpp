#include "Trie.h"

#include "Utilities.h"

Trie::Trie()
    : root(new TrieNode) {
    // The root does not represent a character; all title paths begin below it.
}

Trie::~Trie() {
    // Recursively free all nodes and custom child-list entries.
    deleteNodes(root);
}

TrieNode* Trie::findChild(
    TrieNode* node,
    unsigned char character
) {
    TrieChild* current = node->children;

    // Search the custom linked list for an edge with this character.
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
    // Reuse a shared prefix node when the edge already exists.
    TrieNode* existing = findChild(node, character);
    if (existing != nullptr) {
        return existing;
    }

    // Create the missing node and add its edge at the front of the child list.
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

    // Follow or create one node for each byte in the normalized title.
    for (unsigned char character : key) {
        current = getOrCreateChild(current, character);
    }

    // Store the full record at the terminal node. The vector preserves
    // duplicate titles belonging to different movies or release years.
    current->movies.push_back(movie);
}

bool Trie::search(const std::string& title) const {
    // An exact title exists when searchAll finds at least one terminal record.
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

    // Follow the complete title path. Any missing edge means no exact match.
    for (unsigned char character : key) {
        current = findChild(current, character);

        if (current == nullptr) {
            return {};
        }
    }

    // A nonterminal prefix node naturally returns an empty vector here.
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

    // Navigate to the node representing the complete prefix.
    for (unsigned char character : key) {
        current = findChild(current, character);

        if (current == nullptr) {
            return {};
        }
    }

    // All terminal movies below this node start with the requested prefix.
    std::vector<Movie> results;
    results.reserve(maxResults);
    collectMovies(current, results, maxResults);
    return results;
}

void Trie::collectMovies(
    const TrieNode* node,
    std::vector<Movie>& results,
    std::size_t maxResults
) {
    // Stop recursion once enough suggestions have been collected.
    if (node == nullptr || results.size() >= maxResults) {
        return;
    }

    // Add movies whose complete titles end at the current node.
    for (const Movie& movie : node->movies) {
        if (results.size() >= maxResults) {
            return;
        }

        results.push_back(movie);
    }

    // Recursively visit every title continuation below this prefix.
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

    // Delete descendants and child-list entries before deleting the parent.
    TrieChild* child = node->children;

    while (child != nullptr) {
        TrieChild* nextChild = child->next;
        deleteNodes(child->node);
        delete child;
        child = nextChild;
    }

    delete node;
}
