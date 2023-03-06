//
// Created by sterr on 6/03/2023.
//

#include "Core/Timer/Timer.h"

lightning::Timer::Timer() {
    Reset();
}

void lightning::Timer::Reset() {
    m_StartTime = std::chrono::steady_clock::now();
}

long long lightning::Timer::GetCurrentTimeMicro() const {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m_StartTime).count();
}

float lightning::Timer::GetCurrentTimeMilli() const {
    return GetCurrentTimeMicro() * 0.001f;
}

float lightning::Timer::GetCurrentTimeSec() const {
    return GetCurrentTimeMilli() * 0.001f;
}


