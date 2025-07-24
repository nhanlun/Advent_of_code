cmake_minimum_required(VERSION 3.20)

project(AdventOfCode_2016)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

cmake_policy(SET CMP0167 NEW)
find_package(Boost REQUIRED)

add_executable(day01 day01.cpp)
target_link_libraries(day01 PRIVATE ${Boost_LIBRARIES})
target_include_directories(day01 PRIVATE ${Boost_INCLUDE_DIRS})
add_executable(day02 day02.cpp)
add_executable(day03 day03.cpp)
