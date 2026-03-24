# CMakeLists.txt: Configuration file for building the SortedTemplatedList project.
# Sets up the project, C++ standard, and executable with source files.

cmake_minimum_required(VERSION 4.1)
project(SortedTemplatedList)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortedTemplatedList main.cpp)
