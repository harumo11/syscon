#pragma once
#include <iostream>

class Lowpassfilter1st {
  public:
    Lowpassfilter1st();
    Lowpassfilter1st(const double sampling_frequency,
                     const double cutoff_frequency);
    void setSamplingFrequency(const double sampling_frequency);
    void setCutoffFreqency(const double cutoff_frequency);
    double step(const double latest_value);

  private:
    double previous_input_value = 0;
    double previous_output_value = 0;
    double coeff_previous_input = 0;
    double coeff_current_input = 0;
    double coeff_previous_output = 0;
    double T_sampling = 0;
    double T_cutoff = 0;
};
