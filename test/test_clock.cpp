#include "../syscon/time.hpp"
#include <chrono>
#include <iomanip>

using namespace std::chrono;

int main(int argc, char* argv[])
{
    std::cout << std::setprecision(20) << syscon::time::now() << std::endl;
    system_clock::time_point p = system_clock::now();
    seconds s = duration_cast<seconds>(p.time_since_epoch());
    std::cout << s.count() << std::endl;

    return 0;
}
