cmake_minimum_required(VERSION 3.10)
project(simplexJson)

set(CMAKE_CXX_STANDARD 11)


add_library(simplexJson simplexjson.cpp)
add_executable(main main.cpp)
target_link_libraries(main simplexJson)