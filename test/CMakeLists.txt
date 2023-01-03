cmake_minimum_required(VERSION 3.12)
project(test_for_controlive)
set(CMAKE_CXX_FLAGS "-std=c++20")

find_package(Catch2 3 REQUIRED)

#add_executable(test_clock test_clock.cpp)
add_executable(test_lowpass1 test_lowpass1.cpp)
#target_link_libraries(test_clock PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_lowpass1 PRIVATE Catch2::Catch2WithMain)
