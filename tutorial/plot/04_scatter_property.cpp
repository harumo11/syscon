#include "../../syscon/plot.hpp"
#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "||| This tutorial shows plot property such as title, label, and window size." << std::endl;

    // Make a plot class
    syscon::scatter plot;

    // Set the property
    plot.set_window_size(900, 900);
    plot.set_title("Simple and good scatter plot", 40);
    plot.set_xlabel("simple x label", 20);
    plot.set_ylabel("good   y label", 20);

    // Make the data to be plot.
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0, 4.0 };
    plot.plot(x, x);

    // Plot the data with true option
    std::cout << "Press ENTER key please" << std::endl;
    plot.show(true);
    plot.show(true, true);

    return 0;
}
