cmake_minimum_required(VERSION 2.6)

project(Hangman)

set (Hangman_VERSION_MAJOR 1)
set (Hangman_VERSION_MINOR 0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)

configure_file(
  "${CMAKE_SOURCE_DIR}/include/hangman/version.h.in"
  "${PROJECT_BINARY_DIR}/include/hangman/version.h"
)

include_directories(${CMAKE_SOURCE_DIR}/include
                    ${PROJECT_BINARY_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

enable_testing()
