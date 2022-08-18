cmake_minimum_required(VERSION 3.12)
project(test_controlive)
set(CMAKE_CXX_FLAGS "-std=c++20")

find_package(Catch2 3 REQUIRED)

#add_executable(test_clock test_clock.cpp)
#target_link_libraries(test_clock PRIVATE Catch2::Catch2WithMain)
add_executable(01_scatter_simple_and_realtime 01_scatter_simple_and_realtime.cpp)
add_executable(02_scatter_add_option 02_scatter_add_option.cpp)
