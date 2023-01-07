#pragma once

#include <iostream>
#include <numbers>

namespace syscon {

double T2fc(auto const T)
{
    return 1.0 / (static_cast<double>(T) * 2 * std::numbers::pi);
}

/**
 * @brief convert from cut-off frequency wc [rad/s] to time constant T [s].
 *
 * @param T Time domain [s]
 *
 * @return cut-off frequency [rad/s]
 */
double wc2T(auto const T)
{
    return 1.0 / static_cast<double>(T);
}

double fc2wc(auto const fc)
{
    return 2 * std::numbers::pi * static_cast<double>(fc);
}

double fc2T(auto const fc)
{
    return 1.0 / (2 * std::numbers::pi * static_cast<double>(fc));
}

}
