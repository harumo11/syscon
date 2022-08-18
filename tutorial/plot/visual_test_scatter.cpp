#include "../../controlive/plot.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{

    std::cout << "||| 3rd visual test starts." << std::endl;
    std::cout << "This test describes how to keep to open the plot window." << std::endl;
    cntl::scatter plot3;
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0, 4.0 };
    plot3.plot(x, x);
    plot3.show(true);

    return 0;
}
