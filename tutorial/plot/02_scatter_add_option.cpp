#include "../../syscon/plot.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std::cout << "||| This program describes the differences of enable and disable of add_data option in plot()" << std::endl;

    // Make the plot class.
    syscon::scatter plot2;

    // Make the data to be plot.
    for (double rad = 0; rad < 2 * M_PI; rad += 0.1) {
        double x = std::cos(rad);
        double y = std::sin(rad);
        if (rad < M_PI) {
            // From 0 to pi, plot data with add option.
            plot2.plot(x, y, true);
        } else {
            // From pi to 2pi, plot data without add option.
            plot2.plot(x, y, false);
        }
        plot2.show();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
