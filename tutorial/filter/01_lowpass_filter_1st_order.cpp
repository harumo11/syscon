#include "../../syscon/syscon.hpp"
#include <cmath>
#include <iostream>
#include <numbers>
#include <vector>

int main(int argc, char* argv[])
{
    // low pass filter parameters
    double cutoff_freq = 5;
    double sample_freq = 100;

    // filter setup
    syscon::lowpass1 filter;
    filter.set_filter_params(cutoff_freq, sample_freq);
    auto [coefficients_after, parameters_after] = filter.get_filter_params();

    // print filter coefficients
    std::cout << "||| How to set-up low pass filter" << std::endl;
    std::cout << "y[t] = " << coefficients_after.at(0) << " x[t] + " << coefficients_after.at(1) << " x[t-1] + " << coefficients_after.at(2) << " y[t-1]" << std::endl;
    std::cout << "[cut-off frequency]  = " << cutoff_freq << "Hz" << std::endl;
    std::cout << "[sampling frequency] = " << sample_freq << "Hz" << std::endl;

    // noized signal parameters for test of the fileter
    double dt = 1.0 / sample_freq; // sampling period
    double f1 = 1; // signal frequency [Hz]
    double f2 = 30; // noize frequency [Hz]
    double A1 = 1.0; // Amptitude of signal
    double A2 = 0.3; // amptitude of noize

    syscon::scatter plot_noized;
    syscon::scatter plot_filterd;
    int window_width = 1000;
    int window_height = 800;
    for (int i = 0; i < 1000; i++) {
        double t = dt * i;
        double y1 = A1 * std::sin(2 * std::numbers::pi * f1 * t);
        double y2 = A2 * std::sin(2 * std::numbers::pi * f2 * t);
        double y = y1 + y2;

        double y_filterd = filter.step(y);

        plot_noized.plot(t, y);
        plot_filterd.plot(t, y_filterd);

        plot_noized.show(false, true);
        plot_filterd.show(false, true);
    }

    return 0;
}
