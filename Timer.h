#pragma once
#include <chrono>

class Timer
{
public:
    Timer();

    /// <summary>
    /// returns the timer object
    /// </summary>
    /// <returns></returns>
    static Timer& Get();

    /// <summary>
    /// ticks the timer, should only be called by the game class
    /// </summary>
    void Tick();

    /// <summary>
    /// resets the timer
    /// </summary>
    void Reset();

    double ElapsedMilliseconds() const;

    double ElapsedSeconds() const;

    double TotalMilliseconds() const;

    double TotalSeconds() const;

protected:

private:
    std::chrono::high_resolution_clock::time_point t0, t1;
    double elapsedTime;
    double totalTime;
};
