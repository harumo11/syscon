# CMakeList.txt : controlive の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
find_package(Matplot++ REQUIRED)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable(test_pid_controller TestPidController.cpp PidController.cpp)
add_executable(test_lowpassfilter TestLowpassfilter1st.cpp Lowpassfilter1st.cpp)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
target_link_libraries(test_lowpassfilter PUBLIC Matplot++::matplot)

