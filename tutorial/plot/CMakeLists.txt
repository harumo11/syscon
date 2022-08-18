cmake_minimum_required(VERSION 3.12)
project(test_controlive)
set(CMAKE_CXX_FLAGS "-std=c++20")

find_package(Catch2 3 REQUIRED)

add_executable(01_scatter_simple_and_realtime 01_scatter_simple_and_realtime.cpp)
add_executable(02_scatter_add_option 02_scatter_add_option.cpp)
add_executable(03_scatter_keep_opening_window 03_scatter_keep_opening_window.cpp)
add_executable(04_scatter_property 04_scatter_property.cpp)
