#include <chrono>
#include <iostream>
#include <vector>

namespace controllive {

double diff(const double x_previous, const double x_current, const double t_elapsed)
{
    return (x_current - x_previous) / t_elapsed;
}

} // namespace controllive
