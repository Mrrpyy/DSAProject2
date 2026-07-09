#include "Benchmark.h"
#include "DataLoader.h"
#include "HashTable.h"
#include "Trie.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <string>


void Benchmark::run(const std::vector<Movie>& movies) {
    std::cout << "\n---------- benchmark ----------\n\n";

    

    if (movies.empty()) {
        std::cout << "No movies loaded";

        return;
    }


    // build hash table
    HashTable ht;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < movies.size(); i++) {
        ht.insert(movies[i]);
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> hashBuild = t2 - t1;


    // build trie
   Trie trie;
   
   auto t3 = std::chrono::high_resolution_clock::now();
   for (int i = 0; i < movies.size(); i++) {
    trie.insert(movies[i]);
}

    auto t4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trieBuild = t4 - t3;


    int numMovies = movies.size();
    int count = 1000;
    int searchCount = numMovies < count ? numMovies : count;

    // hash search test
    auto s1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < searchCount; i++) {
        ht.search(movies[i].title);
    }

    auto s2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> hashSearch = s2 - s1;


    // trie search test
    auto s3 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < searchCount; i++) {
        trie.search(movies[i].title);
    }
    
    auto s4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> trieSearch = s4 - s3;


    // print times
    std::cout << "hash build: " << hashBuild.count() << " trie build: " << trieBuild.count() << "\n";
    std::cout << "hash search(" << searchCount << "): " << hashSearch.count()
              << " trie search: " << trieSearch.count() << "\n";



    // autocomplete with a few prefixes
    std::string prefs[] = {"The", "A", "Star", "Harry Pot", "Lor"};

    int numPrefs = 5;

    for (int i = 0; i < numPrefs; i++) {
        auto a1 = std::chrono::high_resolution_clock::now();
        std::vector<Movie> res = trie.autocomplete(prefs[i]);

        auto a2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt = a2 - a1;

        std::cout << prefs[i] << " -> " << res.size() << " in " << dt.count() * 1e6 << " us\n";
    }

    std::cout << "\n--------- done ---------\n";
}