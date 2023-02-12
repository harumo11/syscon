#include "../../syscon/syscon.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    // low pass filter parameters
    double cutoff_freq = 5;
    double sample_freq = 100;

    // filter setup
    syscon::lowpass1 filter(cutoff_freq, sample_freq);

    syscon::bodeplot bode;
    bode.plot(filter);
    bode.show();

    return 0;
}
