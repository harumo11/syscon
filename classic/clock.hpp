#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

/**
 * @brief A class related to time processing. Such as stop watch.
 */
class clock {

public:
    clock();
    std::chrono::steady_clock::time_point previous_called_time;
    double timediff();
    void sleep(const double sleep_seconds);
};

/**
 * @brief A constructor. 
 */
clock::clock()
{
    this->previous_called_time = std::chrono::steady_clock::now();
}

/**
 * @brief Calculates the difference between the current time and the previous time.
 * When this function is called for the first time, the difference seconds is between now and 
 * the time that the constructor was called.
 *
 * @return Returns the difference between the time the function was previously called
 * and the current time. The unit is seconds.
 */
double clock::timediff()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    double duration = std::chrono::duration<double>(now - this->previous_called_time).count();
    this->previous_called_time = now;
    return duration;
}

/**
 * @brief This function stops program execution for the specified seconds.
 * This function stops invoked thread execution with sleep_seconds.
 * sleep_seconds must be bigger than zero. If sleep_seconds is not bigger than zero
 * this function does not sleep.
 *
 * @param sleep_seconds The time that you would like to stop the program. This one must be 
 * begger than zero.
 *
 */
void clock::sleep(const double sleep_seconds)
{
    if (sleep_seconds > 0) {
        auto sleep_duration = std::chrono::duration<double>(sleep_seconds);
        std::this_thread::sleep_for(sleep_duration);
    } else {
        std::cout << "[warn] At clock::sleep( const double sleep_seconds ), invalid sleep_seconds was given. " << std::endl;
        std::cout << "sleep_seconds should be bigger than 0. But " << sleep_seconds << " was given." << std::endl;
        std::cout << "clock::sleep() did NOT sleep this time. " << std::endl;
    }
}
