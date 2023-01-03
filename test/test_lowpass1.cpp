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
    auto [coeffs, params] = filter.get_filter_params();

    CHECK((coeffs.size() == 3));
    CHECK((params.size() == 2));
}

TEST_CASE("Set coefficients of filter at constructor", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;

    syscon::lowpass1 filter(cutoff_freq, sampling_freq);
    auto [coeffs, params] = filter.get_filter_params();

    CHECK((coeffs.size() == 3));
    CHECK((params.size() == 2));
}

TEST_CASE("Check if sampling period is set properly using sampling frequency", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;

    syscon::lowpass1 filter(cutoff_freq, sampling_freq);
    auto [coeffs, params] = filter.get_filter_params();

    CHECK(params.at(0) == (1.0 / sampling_freq));
}

TEST_CASE("Check if time constant is set properly using cut-off frequency", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;

    syscon::lowpass1 filter(cutoff_freq, sampling_freq);
    auto [coeffs, params] = filter.get_filter_params();

    CHECK(params.at(1) == (1.0 / (2 * std::numbers::pi * cutoff_freq)));
}

TEST_CASE("Check for coefficients of filter", "[lowpass1]")
{
    double cutoff_freq = 5;
    double sampling_freq = 100;
    double dt = 1.0 / sampling_freq;
    double T = 1.0 / (2 * std::numbers::pi * cutoff_freq);
    double coeff1 = dt / (dt + 2 * T);
    double coeff2 = -1 * (dt - 2 * T) / (dt + 2 * T);

    syscon::lowpass1 filter(cutoff_freq, sampling_freq);
    auto [coeffs, params] = filter.get_filter_params();

    CHECK(coeffs.at(0) == coeffs.at(1));
    CHECK(coeffs.at(0) == coeff1);
    CHECK(coeffs.at(2) == coeff2);
}
