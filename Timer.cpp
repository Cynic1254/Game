#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
{
    Reset();
}

Timer& Timer::Get()
{
    static Timer t;
    return t;
}

void Timer::Tick()
{
    t1 = high_resolution_clock::now();
    auto delta = t1 - t0;
    t0 = t1;

    elapsedTime = (double)delta.count();
    totalTime += elapsedTime;
}

void Timer::Reset()
{
    t0 = high_resolution_clock::now();
    t1 = t0;

    elapsedTime = 0.0;
    totalTime = 0.0;
}

double Timer::ElapsedMilliseconds() const
{
    return elapsedTime * 1e-6;
}

double Timer::ElapsedSeconds() const
{
    return elapsedTime * 1e-9;
}

double Timer::TotalMilliseconds() const
{
    return totalTime * 1e-6;
}

double Timer::TotalSeconds() const
{
    return totalTime * 1e-9;
}
