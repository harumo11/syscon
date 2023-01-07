#include "../../syscon/syscon.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std::cout << "||| This program shows how to draw simple and realtime scatter plot." << std::endl;

    // Make the plot class.
    syscon::scatter plot1;

    // Make the data and pass them into the plot().
    for (int i = 0; i < 100; i++) {
        double x = i;
        double y = x * x;
        plot1.plot(x, y);

        // plot the data immediately.
        plot1.show();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
