# Require a modern CMake version that supports the commands used below.
cmake_minimum_required(VERSION 3.22)

# Name the project and identify it as a C++ project.
project(MovieSearchEngine LANGUAGES CXX)

# Use the C++17 standard because the program uses std::filesystem.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build one executable from all implementation files in src/.
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

# Allow source files to include headers with statements such as
# #include "Movie.h" instead of specifying the full include/ path.
target_include_directories(MovieSearchEngine PRIVATE include)

# Enable useful compiler warnings without treating them as errors.
if (MSVC)
    target_compile_options(MovieSearchEngine PRIVATE /W4)
else()
    target_compile_options(MovieSearchEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()
