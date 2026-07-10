#pragma once

#include <vector>

#include "Movie.h"

struct TrieNode;

/**
 * Custom linked-list entry connecting a Trie node to one child.
 *
 * This replaces std::unordered_map so the Trie is implemented from scratch.
 */
struct TrieChild {
    // Character represented by the edge from the parent to the child.
    unsigned char character;

    // Child node reached through this character.
    TrieNode* node;

    // Next child edge belonging to the same parent node.
    TrieChild* next;

    TrieChild(
        unsigned char characterValue,
        TrieNode* childNode,
        TrieChild* nextChild = nullptr
    )
        : character(characterValue),
          node(childNode),
          next(nextChild) {}
};

/**
 * One node in the custom Trie.
 *
 * A node can store multiple movies because two or more films can share the
 * same normalized title, such as remakes released in different years.
 */
struct TrieNode {
    // Head of this node's custom linked list of child edges.
    TrieChild* children = nullptr;

    // Movies whose complete normalized title ends at this node.
    std::vector<Movie> movies;
};
