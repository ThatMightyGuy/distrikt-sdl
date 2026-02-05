cmake_minimum_required(VERSION 3.50)
project(Distrikt C VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -ggdb")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(vendor)
add_subdirectory(engine)
add_subdirectory(src)
