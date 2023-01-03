#include "../../syscon/filter.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    double cutoff_freq = 5;
    double sample_freq = 100;

    syscon::lowpass1 filter;
    filter.set_filter_params(cutoff_freq, sample_freq);
    auto [coefficients_after, parameters_after] = filter.get_filter_params();

    std::cout << "||| How to set-up low pass filter" << std::endl;
    std::cout << "y[t] = " << coefficients_after.at(0) << " x[t] + " << coefficients_after.at(1) << " x[t-1] + " << coefficients_after.at(2) << " y[t-1]" << std::endl;
    std::cout << "[cut-off frequency]  = " << cutoff_freq << "Hz" << std::endl;
    std::cout << "[sampling frequency] = " << sample_freq << "Hz" << std::endl;

    return 0;
}
