#pragma once
#include <unordered_map>
struct TrieNode{bool isEndOfWord=false; std::unordered_map<char,TrieNode*> children;};
