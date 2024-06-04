#pragma once

#include <numbers>

namespace syscon {

/**
 * @brief convert from time constant $T$ [s] to cut-off frequency $f_c$ [Hz].
 *
 * $$
 * f_c = \frac{1}{2\pi T}
 * $$
 *
 * @param T Time constant [s]
 *
 * @return cut-off frequency [Hz]
 */
double T2fc(auto const T)
{
    return 1.0 / (static_cast<double>(T) * 2 * std::numbers::pi);
}

/**
 * @brief convert from cut-off frequency $w_c$ [rad/s] to time constant $T$ [s].
 *
 * $$
 * T = \frac{1}{w_c}
 * $$
 *
 * @param wc cuf-off frequency [rad/s]
 *
 * @return Time constant [s]
 */
double wc2T(auto const wc)
{
    return 1.0 / static_cast<double>(wc);
}

/**
 * @brief convert from time constant $T$ [s] to cut-off frequency $w_c$ [rad/s].
 *
 * $$
 * w_c = \frac{1}{T}
 * $$
 *
 * @param T Time constant [s]
 *
 * @return cut-off frequency $w_c$ [rad/s]
 */
double T2wc(auto const T)
{
    return 1.0 / static_cast<double>(T);
}

/**
 * @brief convert from cut-off frequency $f_c$ [Hz] to cut-off frequency $w_c$ [rad/s].
 *
 * $$
 * w_c = 2\pi f_c
 * $$
 *
 * @param fc cut-off frequency [Hz]
 *
 * @return cut-off frequency $w_c$ [rad/s]
 */
double fc2wc(auto const fc)
{
    return 2 * std::numbers::pi * static_cast<double>(fc);
}

/**
 * @brief convert from cut-off frequency $f_c$ [Hz] to time constant $T$ [s].
 *
 * $$
 * T = \frac{1}{2\pi f_c}
 * $$
 *
 * @param fc cut-off frequency [Hz]
 *
 * @return Time constant T [s]
 */
double fc2T(auto const fc)
{
    return 1.0 / (2 * std::numbers::pi * static_cast<double>(fc));
}

}
