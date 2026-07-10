#pragma once

#include <string>

/**
 * Stores all information the program needs about one movie.
 *
 * The ID, title, year, and genre come from title.basics.tsv. The rating and
 * number of votes are added later from title.ratings.tsv by matching IMDb IDs.
 */
struct Movie {
    // IMDb's unique title identifier, for example "tt0111161".
    std::string id;

    // Main title displayed by IMDb and by this program.
    std::string title;

    // Release year. Zero means a valid year was not assigned.
    int year = 0;

    // Average IMDb user rating. Zero means no rating was found.
    float rating = 0.0F;

    // Number of IMDb users who submitted a rating.
    int numVotes = 0;

    // Comma-separated list of genres supplied by IMDb.
    std::string genre;
};
