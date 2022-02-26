#include "PidController.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main(void) {
    PidController controller(0, 0.1, 0.1, 0.1);
    controller.info();

    for (int i = 0; i < 100; i++) {
        std::cout << controller.step(1, 0.3) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        controller.info();
    }
}
