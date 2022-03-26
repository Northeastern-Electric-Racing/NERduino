/**
 * @file timer.h
 * @author Nick DePatie
 * @brief Standardizes the Use of Timers using NERduino
 * @date 2022-03-25
 */

#include <Arduino.h>

class timer
{
    private:
        bool running = 0;
        uint32_t expireTime;

    public:
        timer();
        ~timer();
        void startTimer(uint32_t timeout);
        void cancelTimer();
        bool isTimerExpired();
};
