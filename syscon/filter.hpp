#pragma once

#include "bertrand/include/bertrand/bertrand.hpp"
#include "math.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace syscon {

class lowpass1 {
public:
    const unsigned int filter_order = 1;
    const std::string filter_kind = "First-order system";

    /**
     * @brief The constructor of First-order system.
     * This constructor dose not take any arguments, so use
     * lowpass1::set_filter_params() to pass the filter parameter before you use
     * this filter.
     */
    lowpass1() {};

    /**
     * @brief The constructor of First-order system.
     * This constructor takes all the parameters that needed to start using the
     * filter.
     *
     * @param cutoff_freq The cut off frequency [Hz]
     * @param sample_freq sampling frequency [Hz]
     */
    lowpass1(const double cutoff_freq, const double sample_freq)
    {
        this->filter_coefficients = this->calc_filter_coefficients(cutoff_freq, sample_freq);
    };

    /**
     * @brief Returns the value with high frequency components removed.
     *
     * @param observed_x The new input for this filter.
     * This value is observed by a sensor, etc., and includes high frequency
     * components.
     *
     * @return observed_x without high frequency components.
     */
    double step(const double observed_x)
    {
        Require(this->dt != 0, "Coefficients of filter (sampling period) is not valid. Did you set filter parameters?");
        Require(this->time_constant != 0, "Coefficients of filter (time constant) is not valid. Did you set filter parameters?");

        // shift x with one element and update with new observed value
        this->x.at(0) = this->x.at(1);
        this->x.at(1) = observed_x;

        double y = this->filter_coefficients.at(0) * this->x.at(0) + this->filter_coefficients.at(1) * this->x.at(1) + this->filter_coefficients.at(2) * this->y_previous;

        this->y_previous = y;
        return y;
    };

    /**
     * @brief Returns coefficients and parameter of filter.
     *
     * @return Returns tuple including two vector.
     * - vector1 : coefficients of filter (c1~c3)
     *   y[t] = c1 * x[t] + c2 * x[t-1] + c3 * y[t-1]
     *
     * - vector2 : time parameters of filter
     *   - sampling time [s]
     *   - time constant [s]
     */
    std::tuple<std::vector<double>, std::vector<double>> get_filter_params()
    {
        return { this->filter_coefficients, { this->dt, this->time_constant } };
    };

    /**
     * @brief Set cut-off frequency and sampling frequency of filter.
     *
     * @param cutoff_freq cut-off frequency [Hz].
     * @param sample_freq samplilng frequency to observe data [Hz].
     */
    void set_filter_params(const double cutoff_freq, const double sample_freq)
    {
        this->filter_coefficients = this->calc_filter_coefficients(cutoff_freq, sample_freq);
    };

    // TODO implementation is needed.
    std::tuple<std::vector<double>, std::vector<double>> frequency_response()
    {
        return { { 0 }, { 0 } };
    };

private:
    double dt = 0; // sampling period [s]
    double time_constant = 0; // [s]
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
    std::vector<double> calc_filter_coefficients(const double cutoff_freq,
        const double sample_freq)
    {
        Require(cutoff_freq > 0, "Set a number bigger than 0 for the cut-off frequency.");
        Require(sample_freq > 0, "Set a number bigger than 0 for the sampling frequency.");
        Require(sample_freq >= cutoff_freq, "sampling frequency >= cut-off frequency.");

        // convert sampling frequency [Hz] to sampling period [s]
        this->dt = 1.0 / sample_freq;
        // convert cut-off frequency [Hz] to time constant [s]
        this->time_constant = fc2T(cutoff_freq);
        // calculate coefficients of filter
        std::vector<double> calculated_filter_coefficients = { 0, 0, 0 };
        calculated_filter_coefficients.at(0) = this->dt / (this->dt + 2 * this->time_constant);
        calculated_filter_coefficients.at(1) = this->dt / (this->dt + 2 * this->time_constant);
        calculated_filter_coefficients.at(2) = -1 * (this->dt - 2 * this->time_constant) / (this->dt + 2 * this->time_constant);

        return calculated_filter_coefficients;
    };
};

} // namespace syscon
