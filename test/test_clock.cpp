#include "../controlive/time.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <thread>

TEST_CASE("Measure one second", "[clock]")
{
    controlive::clock c;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    CHECK(c.seconds_from_previous_call() == Catch::Approx(1).epsilon(0.001));
}

TEST_CASE("Sleep one second", "[clock]")
{
    auto start_time = std::chrono::high_resolution_clock::now();
    controlive::clock::sleep(1.0);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto diff_time = controlive::clock::time_difference(start_time, end_time);
    CHECK(diff_time == Catch::Approx(1).epsilon(0.001));
}
