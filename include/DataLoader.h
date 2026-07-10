#pragma once

#include <string>
#include <vector>

#include "Movie.h"

/**
 * Reads the two IMDb TSV files and converts their rows into Movie objects.
 *
 * Data loading is kept separate from the search structures so the Trie and
 * HashTable classes only need to work with a vector of already-cleaned movies.
 */
class DataLoader {
public:
    /**
     * Loads movie details and merges matching rating information.
     *
     * @param basicsFile  Path to title.basics.tsv.
     * @param ratingsFile Path to title.ratings.tsv.
     * @return All valid rows whose title type is "movie" and whose year exists.
     */
    std::vector<Movie> loadMovies(
        const std::string& basicsFile,
        const std::string& ratingsFile
    );

private:
    /**
     * Splits one line into fields using the supplied delimiter.
     * IMDb uses tab characters, so loadMovies normally passes '\t'.
     */
    static std::vector<std::string> splitLine(
        const std::string& line,
        char delimiter
    );
};
