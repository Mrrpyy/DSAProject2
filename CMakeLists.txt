
cmake_minimum_required(VERSION 3.22)

project(MovieSearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MovieSearchEngine
        src/main.cpp
        src/Movie.cpp
        src/DataLoader.cpp
        src/Trie.cpp
        src/HashTable.cpp
        src/Benchmark.cpp
        src/Menu.cpp
        src/Utilities.cpp
)

target_include_directories(MovieSearchEngine PRIVATE include)

if (MSVC)
    target_compile_options(MovieSearchEngine PRIVATE /W4)
else()
    target_compile_options(MovieSearchEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()
