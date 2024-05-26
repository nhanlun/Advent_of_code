cmake_minimum_required(VERSION 3.20)

project(AdventOfCode_2015)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(fmt)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(day15 day15.cpp)
target_include_directories(day15 SYSTEM PUBLIC "D:/Project_mini/dependencies/eigen-3.4.0")

add_executable(day16 day16.cpp)

add_executable(day17 day17.cpp)

add_executable(day18 day18.cpp)

add_executable(day19 day19.cpp)

add_executable(day20 day20.cpp)
