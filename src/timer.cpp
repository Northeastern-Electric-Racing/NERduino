#include "timer.h"

timer::timer(){}

timer::~timer(){}

void timer::startTimer(uint32_t timeout)
{
    running = true;
    expireTime = millis() + timeout;
}

void timer::cancelTimer()
{
    running = false;
    expireTime = millis();
}

bool timer::isTimerExpired()
{
    if(!running)
    {
        return false;
    }

    return expireTime > millis() ? false : true;
}