cmake_minimum_required(VERSION 3.14)
project(tripletriad CXX)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(tests)
