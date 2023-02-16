cmake_minimum_required(VERSION 3.12)

project(tutorial_filter)
set(CMAKE_CXX_FLAGS "-std=c++20")

add_executable(01_lowpass_filter_1st_order      01_lowpass_filter_1st_order.cpp)
add_executable(02_lowpass_filter_1st_order_bode 02_lowpass_filter_1st_order_bode.cpp)
