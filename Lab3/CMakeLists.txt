cmake_minimum_required(VERSION 3.15)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab3 main.cpp tests.h cmake-build-debug/priority_queue.h priority_queue.cpp binary_search_tree.h priority_queue.h binary_search_tree.cpp)