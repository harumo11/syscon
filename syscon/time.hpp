#pragma once

#include <chrono>
#include <codecvt>
#include <iostream>

namespace syscon::time {

/**
 * @brief Current time
 * Return a current time[sec] since epoch time as double.
 *
 * @return curren time [sec]
 */
double now()
{
    auto current_time = std::chrono::system_clock::now();
    auto duration_in_sec = std::chrono::duration<double>(current_time.time_since_epoch());
    return duration_in_sec.count();
}

/**
 * @brief non
 */
class clock {

public:
    /**
     * @brief enen
     */
    clock();
};

clock::clock()
{
}

} // namespace syscon
