#include "../controlive/plot.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std::cout << "||| 1st visual test start." << std::endl;
    cntl::scatter plot1;
    for (int i = 0; i < 100; i++) {
        double x = i;
        double y = x * x;
        plot1.plot(x, y);
        plot1.show();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "||| 1st test finish. Press Enter key." << std::endl;

    std::cout << "||| 2nd visual test start." << std::endl;
    cntl::scatter plot2;
    for (int i = 0; i < 100; i++) {
        double x = i;
        double y = x * x;
        if (i < 50) {
            plot2.plot(x, y);
        } else {
            plot2.plot(x, y, false);
        }
        plot2.show();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "||| 2nd test finish. Press Enter key." << std::endl;
    return 0;
}
