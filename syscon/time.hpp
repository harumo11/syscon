#include <chrono>
#include <codecvt>
#include <iostream>

namespace syscon::time {
double now()
{
    auto current_time = std::chrono::system_clock::now();
    auto duration_in_sec = std::chrono::duration<double>(current_time.time_since_epoch());
    return duration_in_sec.count();
}
} // namespace syscon
