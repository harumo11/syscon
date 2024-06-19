#pragma once

#include "./third_pary/bertrand/include/bertrand/bertrand.hpp"
#include "math.hpp"
#include <algorithm>
#include <complex>
#include <string>
#include <tuple>
#include <vector>

namespace syscon {

/**
 * @brief A class of first-order lowpass filter that can smoothes the input signal.
 *
 * This filter smoothes the input signal
 * using filter coefficients and past output values to generate
 * an output signal with high frequency components removed.
 *
 * The smoothed output, filter coefficients, and past output
 * are expressed by following formura.
 *
 * $y[t] = c_1 x[t] + c_2 x[t-1] + c_3 y[t-1]$.
 *
 * - $[t]$ : Time step
 * - $y[t]$ : Smoothed output that removed high frequency components.
 * - $x[t]$ : Input signal that includes high frequency components.
 * - $c_1$~$c_3$ : Coefficients of the filter.
 *
 */
class lowpass1 {
public:
    const unsigned int filter_order = 1;
    const std::string filter_kind = "First-order system";

    /**
     * @brief The constructor of a low pass filter of first-order system.
     *
     * This constructor dose not take any arguments, so use
     * lowpass1::set_filter_params() to pass the filter parameter before you use
     * this filter.
     */
    lowpass1() { }

    /**
     * @brief The constructor of a low pass filter of first-order system.
     *
     * This constructor takes all the information needed to user the filter.
     * Then, it calculates the filter coefficients internally.
     *
     * ```
     * double cut_off_frequency = 20; //20Hz
     * double sampling_frequency = 100; // 100Hz
     *
     * syscon::lowpass1 filter(cut_off_frequency, sampling_frequency);
     * ```
     *
     * @param cutoff_freq The cut off frequency [Hz]
     * @param sample_freq sampling frequency [Hz]
     */
    lowpass1(const double cutoff_freq, const double sample_freq)
    {
        this->filter_coefficients = this->calc_filter_coefficients(cutoff_freq, sample_freq);
    }

    /**
     * @brief Returns a signal that high frequency components removed.
     *
     * @param observed_x The new input for this filter.
     * This value is observed by a sensor, etc., and includes high frequency
     * components.
     *
     *``` cpp
     *
     * syscon::lowpass1 filter(20, 100);
     * while(true)
     * {
     *      sensor_signal = get_sensor_data();
     *      signal = filter.step(sensor_signal);
     * }
     *
     *```
     *
     * @return A signal from witch frequency components more than the cutoff frequency is removed.
     */
    double step(const double observed_x)
    {
        Require(this->dt != 0, "Coefficients of filter (sampling period) is not valid. Did you set filter parameters?");
        Require(this->T != 0, "Coefficients of filter (time constant) is not valid. Did you set filter parameters?");

        // shift x with one element and update with new observed value
        this->x.at(0) = this->x.at(1);
        this->x.at(1) = observed_x;

        double y = this->filter_coefficients.at(0) * this->x.at(0) + this->filter_coefficients.at(1) * this->x.at(1) + this->filter_coefficients.at(2) * this->y_previous;

        this->y_previous = y;
        return y;
    }

    /**
     * @brief Returns coefficients and parameters of the filter.
     *
     * ```c++
     * double cutoff_freq = 5;
     * double sample_freq = 100;
     *
     * syscon::lowpass1 filter(cutoff_freq, sample_freq);
     * auto [coefficients, parameters] = filter.get_filter_params();
     *
     * std::cout << "y[t] = coefficients.at(0) << "x[t] + " << coefficients.at(1) << "x[t-1] + " << coefficients.at(2) << "y[t-1]" << std::endl;
     * std::cout << "[sampling period] = " << parameters.at(0) << " [s]" << std::endl;
     * std::cout << "[time constant  ] = " << parameters.at(1) << " [s]" << std::endl;
     *
     * ----------------------
     * y[t] = 0.135755 x[t] + 0.135755 x[t-1] + 0.72849 y[t-1]
     * [sampling period   ] = 0.01s
     * [time constant     ] = 0.031831s
     *
     * ```
     *
     * @return Returns coefficients and parameters of the low pass filter.
     *
     * - Coefficients of the filter ($c_1$~$c_3$) in
     *   $y[t] = c_1 x[t] + c_2 x[t-1] + c_3 y[t-1]$.
     *
     * - Time parameters of the filter : Sampling period [s] and time constant [s].
     *
     */
    std::tuple<std::vector<double>, std::vector<double>> get_filter_params()
    {
        return { this->filter_coefficients, { this->dt, this->T } };
    }

    /**
     * @brief Set cut-off frequency and sampling frequency of filter.
     *
     * @param cutoff_freq cut-off frequency [Hz].
     * @param sample_freq samplilng frequency to observe data [Hz].
     */
    void set_filter_params(const double cutoff_freq, const double sample_freq)
    {
        this->filter_coefficients = this->calc_filter_coefficients(cutoff_freq, sample_freq);
    }

    /**
     * @brief calculates multiple frequency responsese of the filter.
     *
     * @param omega This vector contains the anguler frequencies [rad/s] for which
     * you want to know the frequency response of the filter.
     *
     * @return Three vectors reresent magnitude, phase, and, anguler frequency respectively.
     * Anguler frequencies are sorted in ascending order.
     * The magnitude and phase contains the frequency response correspoing to omega.
     * For example, the response at `omega.at(2)` is in `magnitude.at(2)` and `phase.at(2)`.
     *
     */
    std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> frequency_response(std::vector<double> omega)
    {
        Require(omega.size() > 0, "The size of omega vector is zero. That size must be bigger than zero.");
        auto negative_value_index = std::find_if(omega.begin(), omega.end(), [](double omega) { return omega < 0; });
        Require(negative_value_index == omega.end(), "Omega vector has negative value. Omega must be bigger than or equal to zero.");

        std::vector<double> mag;
        std::vector<double> phase;
        std::sort(omega.begin(), omega.end());

        for (auto&& w : omega) {
            auto G = this->continuous_frequency_represent(w);
            mag.push_back(20 * std::log10(std::abs(G)));
            phase.push_back(std::arg(G));
        }

        return { mag, phase, omega };
    }

private:
    double dt = 0; // sampling period [s]
    double T = 0; // [s]
    double y_previous = 0; // filterd output at t-1
    std::vector<double> x = { 0, 0 }; // input t-1 and t
    std::vector<double> filter_coefficients = { 0, 0, 0 }; // three coefficients of filter.

    /**
     * @brief Calculates three coefficients of filter from cut-off frequency and
     * sampling frequency.
     *
     * @param cutoff_freq cut-off frequency [Hz].
     * @param sample_freq samplilng frequency to observe data [Hz].
     *
     * @return Three coefficients of filter. Values for c1 to c3 in the below
     * equation. y[t] = c1 * x[t] + c2 * x[t-1] + c3 * y[t-1]
     */
    std::vector<double> calc_filter_coefficients(const double cutoff_freq, const double sample_freq)
    {
        Require(cutoff_freq > 0, "Set a number bigger than 0 for the cut-off frequency.");
        Require(sample_freq > 0, "Set a number bigger than 0 for the sampling frequency.");
        Require(sample_freq >= cutoff_freq, "sampling frequency >= cut-off frequency.");

        // convert sampling frequency [Hz] to sampling period [s]
        this->dt = 1.0 / sample_freq;
        // convert cut-off frequency [Hz] to time constant [s]
        this->T = fc2T(cutoff_freq);
        // calculate coefficients of filter
        std::vector<double> calculated_filter_coefficients = { 0, 0, 0 };
        calculated_filter_coefficients.at(0) = this->dt / (this->dt + 2 * this->T);
        calculated_filter_coefficients.at(1) = this->dt / (this->dt + 2 * this->T);
        calculated_filter_coefficients.at(2) = -1 * (this->dt - 2 * this->T) / (this->dt + 2 * this->T);

        return calculated_filter_coefficients;
    }

    /**
     * @brief Returns the magnitude and phase at specified omega [rad/s] as the continuous system.
     *
     * When w[rad/s] is specified, {real, imag} of G(jw) is returned with following equation.
     * G(jw) = real + j * imag
     * real = 1 / (1 + w^2 * T^2)
     * imag = (-wT) / (1 + w^2 * T^2)
     *
     * @param omega Angular velocity [rad/s] that you want to know the filter frequency response.
     *
     * @return frequency response with specified w. Returned value is represents with complex type.
     */
    std::complex<double> continuous_frequency_represent(const double omega)
    {
        Require(omega >= 0, "Angular velocity w [rad/s] bigger than zero.");
        Require(this->T >= 0, "Time constant T is not valid valued. Did you set filter parameter?");

        // G(jw) = real + j * imag
        double real = 1.0 / (1 + omega * omega * this->T * this->T);
        double imag = (-1 * omega * this->T) / (1 + omega * omega * this->T * this->T);
        std::complex<double> G(real, imag);
        return G;
    }
};

} // namespace syscon
