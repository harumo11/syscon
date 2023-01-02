#include "../syscon/filter.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <thread>

TEST_CASE("Set coefficients of filter", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;

    syscon::lowpass1 filter;
    filter.set_filter_params(cutoff_freq, sampling_freq);
    auto [params1, params2] = filter.get_filter_params();

    CHECK((params1.size() == 3) && (params2.size() == 2));
}

TEST_CASE("Set coefficients of filter at constructor", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;

    syscon::lowpass1 filter(cutoff_freq, sampling_freq);
    auto [coeff, params] = filter.get_filter_params();

    CHECK((params.size() == 3) && (params.size() == 2));
}

TEST_CASE("Check if sampling period is set properly using sampling frequency", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;

    syscon::lowpass1 filter(cutoff_freq, sampling_freq);
    auto [coeff, params] = filter.get_filter_params();

    CHECK(params.at(0) == (1.0 / sampling_freq));
}

TEST_CASE("Check if time constant is set properly using cut-off frequency", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;

    syscon::lowpass1 filter(cutoff_freq, sampling_freq);
    auto [coeff, params] = filter.get_filter_params();

    CHECK(params.at(1) == (1.0 / (2 * std::numbers::pi * cutoff_freq)));
}

TEST_CASE("Check for coefficients of filter", "[lowpass1]")
{
    // TODO implemenation!
    CHECK(true);
}
