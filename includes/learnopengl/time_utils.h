#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <chrono>

namespace TimeUtils
{
    inline double GetTime()
    {
        static const auto start_time = std::chrono::steady_clock::now();
        auto current_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = current_time - start_time;
        return elapsed.count();
    }
}

#endif // TIME_UTILS_H