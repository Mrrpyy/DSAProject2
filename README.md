# Movie Search Engine

## Team Members

- Brian Tang 
- Member 2
- Member 3

## Project Description

A movie search engine that compares the performance of a Trie and a Hash Table for searching large movie datasets.

## Dataset

Download:

- title.basics.tsv
- title.ratings.tsv

Place them inside:

data/

## Build

Open the project in CLion.

Build using CMake.

Run:

MovieSearchEngine

## Features

- Load IMDb datasets
- Search movies
- Autocomplete
- Benchmark Trie vs Hash Table

MovieSearchEngine/
│
├── CMakeLists.txt
├── README.md
├── .gitignore
│
├── data/
│   ├── title.basics.tsv        (Do not push to git)
│   └── title.ratings.tsv       (Do not push to git)
│
├── include/
│   ├── Movie.h
│   ├── DataLoader.h
│   ├── Trie.h
│   ├── TrieNode.h
│   ├── HashTable.h
│   ├── HashNode.h
│   ├── Benchmark.h
│   ├── Menu.h
│   └── Utilities.h
│
├── src/
│   ├── main.cpp
│   ├── Movie.cpp
│   ├── DataLoader.cpp
│   ├── Trie.cpp
│   ├── HashTable.cpp
│   ├── Benchmark.cpp
│   ├── Menu.cpp
│   └── Utilities.cpp
│
├── tests/
│   ├── DataLoaderTests.cpp
│   ├── TrieTests.cpp
│   └── HashTableTests.cpp
