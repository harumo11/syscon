#include "../../controlive/plot.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std::cout << "||| 1st visual test start." << std::endl;
    std::cout << "This test describes simply how to plot." << std::endl;
    cntl::scatter plot1;
    for (int i = 0; i < 100; i++) {
        double x = i;
        double y = x * x;
        plot1.plot(x, y);
        plot1.show();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "||| 1st test finish. Press Enter key." << std::endl;
    std::cin.get();

    std::cout << "||| 2nd visual test start." << std::endl;
    std::cout << "This test describes differences of enable and disable of add_data option in plot()" << std::endl;
    cntl::scatter plot2;
    for (double rad = 0; rad < 2 * M_PI; rad += 0.1) {
        double x = std::cos(rad);
        double y = std::sin(rad);
        if (rad < M_PI) {
            plot2.plot(x, y);
        } else {
            plot2.plot(x, y, false);
        }
        plot2.show();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "||| 2nd test finish. Press Enter key." << std::endl;
    std::cin.get();

    std::cout << "||| 3rd visual test starts." << std::endl;
    std::cout << "This test describes how to keep to open the plot window." << std::endl;
    cntl::scatter plot3;
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0, 4.0 };
    plot3.plot(x, x);
    plot3.show(true);

    return 0;
}
