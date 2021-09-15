#include "Lowpassfilter1st.hpp"
#include <iostream>

Lowpassfilter1st::Lowpassfilter1st() {}

Lowpassfilter1st::Lowpassfilter1st(const double sampling_frequency,
                                   const double cutoff_frequency) {
    this->T_sampling = 1.0 / sampling_frequency;
    this->T_cutoff = 1.0 / cutoff_frequency;

    this->coeff_current_input = (T_sampling) / (2 * T_cutoff + T_sampling);
    this->coeff_previous_input = this->coeff_current_input;
    this->coeff_previous_output =
        (2 * T_cutoff - 2 * T_sampling) / (2 * T_cutoff + T_sampling);
}

void Lowpassfilter1st::setCutoffFreqency(const double cutoff_frequency) {
    this->T_cutoff = 1.0 / cutoff_frequency;
}

void Lowpassfilter1st::setSamplingFrequency(const double sampling_frequency) {
    this->T_sampling = 1.0 / sampling_frequency;
}

double Lowpassfilter1st::step(const double latest_value) {
    const double filtered_output =
        this->coeff_current_input * latest_value +
        this->coeff_previous_input * this->previous_input_value +
        this->coeff_previous_output * this->previous_output_value;

    this->previous_input_value = latest_value;
    this->previous_output_value = filtered_output;

    return filtered_output;
}
