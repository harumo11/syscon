# CMakeList.txt : 最上位の CMake プロジェクト ファイル。グローバル構成を行います
# また、サブプロジェクトをここに含めます。
#
cmake_minimum_required (VERSION 3.8)

project ("controlive")
find_package(Eigen3 CONFIG REQUIRED)

# サブプロジェクトを含めます。
add_subdirectory ("Classic")
