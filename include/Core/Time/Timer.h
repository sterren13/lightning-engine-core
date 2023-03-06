//
// Created by sterr on 6/03/2023.
//

#ifndef CORE_TIMER_H
#define CORE_TIMER_H
#include <chrono>

namespace lightning {
    class Timer {
    public:
        Timer();

        void Reset();

        long long GetCurrentTimeMicro() const;
        float GetCurrentTimeMilli() const;
        float GetCurrentTimeSec() const;

    private:
        std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
    };
}

#endif //CORE_TIMER_H
