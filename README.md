# Movie Search Engine

A C++17 console application that compares a custom Trie with a custom
separate-chaining Hash Table on 100,000 IMDb movie records.

## Team Members

- Brian Tang — `Mrrpyy`
- Guilherme Beltrao Carvalheira — `belgbcarv`
- Omar Porven Miranda — `slomar1`

## Features

- Loads and combines IMDb movie and rating TSV files
- Filters the dataset to movie records with valid release years
- Exact, case-insensitive title search
- Duplicate-title support for remakes and reused titles
- Trie autocomplete limited to 10 suggestions
- Build-time benchmarking
- Successful and unsuccessful exact-search benchmarking
- Hash Table capacity and collision statistics
- Interactive console menu

## Custom Data Structures

### Trie

The Trie is implemented from scratch. Each node uses a custom linked list of
child entries rather than a library map. It supports exact title lookup and
prefix autocomplete.

### Hash Table

The Hash Table is implemented from scratch using separate chaining, a custom
polynomial hash function, prime-number capacities, and dynamic resizing when
the load factor would exceed 0.75.

## Dataset Setup

Download and extract these files from the official IMDb datasets page:

- `title.basics.tsv.gz`
- `title.ratings.tsv.gz`

Place the extracted files here:

```text
data/title.basics.tsv
data/title.ratings.tsv
```

The full dataset files are excluded from Git because they are too large for
GitHub.

## Run in CLion

1. Clone or download this repository.
2. Open the repository folder in CLion.
3. Put both extracted IMDb TSV files in the `data/` folder.
4. Reload the CMake project when prompted.
5. Select the `MovieSearchEngine` run configuration.
6. Build and run the project.

## Command-Line Build

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

Run on macOS or Linux:

```bash
./build/MovieSearchEngine
```

Run on Windows when using a single-configuration generator:

```powershell
.\build\MovieSearchEngine.exe
```

## Menu

```text
1. Search for an exact movie title
2. Autocomplete a movie title
3. Run Trie vs Hash Table benchmark
4. Exit
```

## Dataset Size

`src/main.cpp` currently limits the interactive program to 100,000 movies,
which satisfies the assignment requirement. Change `datasetLimit` to use a
larger portion of the IMDb dataset.

## Repository Structure

```text
DSAProject2/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── data/
│   └── README.md
├── include/
│   ├── Benchmark.h
│   ├── DataLoader.h
│   ├── HashNode.h
│   ├── HashTable.h
│   ├── Menu.h
│   ├── Movie.h
│   ├── Trie.h
│   ├── TrieNode.h
│   └── Utilities.h
└── src/
    ├── Benchmark.cpp
    ├── DataLoader.cpp
    ├── HashTable.cpp
    ├── Menu.cpp
    ├── Movie.cpp
    ├── Trie.cpp
    ├── Utilities.cpp
    └── main.cpp
```
