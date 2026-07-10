# Movie Search Engine

A C++ movie search engine that compares a custom Trie with a custom chained Hash Table on at least 100,000 IMDb movie records.

## Team Members

- Brian Tang — `Mrrpyy`
- Guilherme Beltrao Carvalheira — belgbcarv
- Omar Porven Miranda — slomar1

## Features

- Loads IMDb movie and rating data from TSV files
- Exact, case-insensitive movie-title search
- Trie autocomplete with a 10-result limit
- Duplicate-title support
- Build-time and exact-search benchmarking
- Hash Table collision statistics
- Console menu

## Dataset Setup

Download and extract these files from the official IMDb datasets page:

- `title.basics.tsv.gz`
- `title.ratings.tsv.gz`

After extraction, place the files here:

```Data
data/title.basics.tsv
data/title.ratings.tsv
```
The full dataset files are intentionally excluded from Git because they are too large for GitHub.

## Run in CLion

1. Clone or download this repository.
2. Open the repository folder in CLion.
3. Put the two extracted IMDb TSV files in the `data` folder.
4. Reload the CMake project if prompted.
5. Select the `MovieSearchEngine` run configuration.
6. Build and run.

## Command-Line Build

```bash
cmake -S . -B build
cmake --build build
./build/MovieSearchEngine
```

## Data Structures

### Trie

The Trie is implemented from scratch. Each node stores its children in a custom linked structure. It supports exact title lookup and prefix autocomplete.

### Hash Table

The Hash Table is implemented from scratch with separate chaining, dynamic resizing, and a custom polynomial hash function. It supports exact title lookup.

## Notes
- Change `datasetLimit` in `src/main.cpp` to benchmark a larger dataset.
