cmake_minimum_required(VERSION 3.3)
project(TSP-SA)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_subdirectory(src)
