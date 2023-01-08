# CMakeList.txt : 最上位の CMake プロジェクト ファイル。グローバル構成を行います
# また、サブプロジェクトをここに含めます。
#
cmake_minimum_required (VERSION 3.12)

project ("syscon")

include_directories(syscon)
add_subdirectory(test)
add_subdirectory(tutorial/filter)
add_subdirectory(tutorial/plot)
