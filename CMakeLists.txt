cmake_minimum_required(VERSION 3.22)
project(MovieSearchEngine)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(MovieSearchEngine
    src/main.cpp
    src/Movie.cpp
    src/Trie.cpp
    src/HashTable.cpp
    src/DataLoader.cpp
    src/Benchmark.cpp
    src/Menu.cpp
    src/Utilities.cpp
)
