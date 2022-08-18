#include "../../controlive/plot.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std::cout << "This test describes how to keep to open the plot window." << std::endl;

    // Make a plot class.
    cntl::scatter plot;

    // Make the data to be plot.
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0, 4.0 };

    // Set the data.
    plot.plot(x, x);

    // Plot the data with true option.
    plot.show(true);

    return 0;
}
