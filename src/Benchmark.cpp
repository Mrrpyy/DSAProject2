#include "Benchmark.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "HashTable.h"
#include "Trie.h"

void Benchmark::run(const std::vector<Movie>& movies) const {
    using Clock = std::chrono::steady_clock;

    if (movies.empty()) {
        std::cout << "No movies are loaded.\n";
        return;
    }

    std::cout << "\n========== BENCHMARK ==========\n";
    std::cout << "Dataset size: " << movies.size() << " movies\n\n";

    HashTable hashTable;
    const auto hashBuildStart = Clock::now();
    for (const Movie& movie : movies) {
        hashTable.insert(movie);
    }
    const auto hashBuildEnd = Clock::now();

    Trie trie;
    const auto trieBuildStart = Clock::now();
    for (const Movie& movie : movies) {
        trie.insert(movie);
    }
    const auto trieBuildEnd = Clock::now();

    const double hashBuildSeconds =
        std::chrono::duration<double>(hashBuildEnd - hashBuildStart).count();
    const double trieBuildSeconds =
        std::chrono::duration<double>(trieBuildEnd - trieBuildStart).count();

    const std::size_t queryCount = std::min<std::size_t>(5000, movies.size());
    const std::size_t step = std::max<std::size_t>(1, movies.size() / queryCount);

    std::vector<std::string> successfulQueries;
    successfulQueries.reserve(queryCount);

    for (std::size_t i = 0; i < movies.size() && successfulQueries.size() < queryCount; i += step) {
        successfulQueries.push_back(movies[i].title);
    }

    std::vector<std::string> unsuccessfulQueries;
    unsuccessfulQueries.reserve(successfulQueries.size());
    for (const std::string& title : successfulQueries) {
        unsuccessfulQueries.push_back(title + " __TITLE_NOT_IN_DATASET__");
    }

    constexpr int rounds = 3;
    volatile std::size_t resultSink = 0;

    const auto measureHash = [&](const std::vector<std::string>& queries) {
        const auto start = Clock::now();
        for (int round = 0; round < rounds; ++round) {
            for (const std::string& query : queries) {
                if (hashTable.search(query) != nullptr) {
                    ++resultSink;
                }
            }
        }
        const auto end = Clock::now();
        return std::chrono::duration<double, std::nano>(end - start).count() /
               static_cast<double>(queries.size() * rounds);
    };

    const auto measureTrie = [&](const std::vector<std::string>& queries) {
        const auto start = Clock::now();
        for (int round = 0; round < rounds; ++round) {
            for (const std::string& query : queries) {
                if (trie.search(query)) {
                    ++resultSink;
                }
            }
        }
        const auto end = Clock::now();
        return std::chrono::duration<double, std::nano>(end - start).count() /
               static_cast<double>(queries.size() * rounds);
    };

    const double hashSuccessfulNs = measureHash(successfulQueries);
    const double trieSuccessfulNs = measureTrie(successfulQueries);
    const double hashUnsuccessfulNs = measureHash(unsuccessfulQueries);
    const double trieUnsuccessfulNs = measureTrie(unsuccessfulQueries);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Build time\n";
    std::cout << "  Hash Table: " << hashBuildSeconds << " seconds\n";
    std::cout << "  Trie:       " << trieBuildSeconds << " seconds\n\n";

    std::cout << "Average exact-search time (" << successfulQueries.size()
              << " queries, " << rounds << " rounds)\n";
    std::cout << "  Successful Hash Table: " << hashSuccessfulNs << " ns/query\n";
    std::cout << "  Successful Trie:       " << trieSuccessfulNs << " ns/query\n";
    std::cout << "  Missing Hash Table:    " << hashUnsuccessfulNs << " ns/query\n";
    std::cout << "  Missing Trie:          " << trieUnsuccessfulNs << " ns/query\n\n";

    std::cout << "Hash Table statistics\n";
    std::cout << "  Capacity:   " << hashTable.getCapacity() << '\n';
    std::cout << "  Collisions: " << hashTable.getCollisionCount() << '\n';

    const std::vector<std::string> prefixes = {"the", "star", "harry", "love"};
    std::cout << "\nTrie autocomplete (maximum 10 results)\n";

    for (const std::string& prefix : prefixes) {
        const auto start = Clock::now();
        const std::vector<Movie> results = trie.autocomplete(prefix, 10);
        const auto end = Clock::now();

        const double microseconds =
            std::chrono::duration<double, std::micro>(end - start).count();

        resultSink += results.size();
        std::cout << "  \"" << prefix << "\": " << results.size()
                  << " results in " << microseconds << " us\n";
    }

    std::cout << "===============================\n";
}
