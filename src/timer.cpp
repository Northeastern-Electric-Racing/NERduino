#include "timer.h"

Timer::Timer()
{
    cancelTimer();
}

Timer::~Timer(){}

void Timer::startTimer(uint32_t timeout)
{
    running_ = true;
    expire_time_ = millis() + timeout;
    is_reset_ = 0;
}

void Timer::cancelTimer()
{
    running_ = false;
    expire_time_ = millis();
    is_reset_ = 1;
}

bool Timer::isTimerExpired()
{
    if(!running_)
    {
        return true;
    }

    return expire_time_ > millis() ? false : true;
}

bool Timer::isTimerReset()
{
    return is_reset_;
}