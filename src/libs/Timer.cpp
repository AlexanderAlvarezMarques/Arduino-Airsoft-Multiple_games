#include "Timer.h"
#include <Arduino.h>

Timer::Timer() {}

void Timer::start(int _updateAt) {
    updateAt = _updateAt;
    lastTimeStamp = millis();
    isPaused = false;
}

void Timer::pause() {
    isPaused = true;
}

void Timer::resume() {
    isPaused = false;
    lastTimeStamp = millis(); // Resume from the current time
}

void Timer::stop() {
    lastTimeStamp = 0; // Reset the lastTimeStamp to stop the timer
}

long Timer::getInterval() {
    if (isPaused) {
        return lastTimeStamp; // If paused, return the last recorded time
    }
    const long currentTime = millis();

    return currentTime - lastTimeStamp;
}

int Timer::getIntervalInSeconds() {
    long diff = getInterval();
    int seconds = diff / 1000;
    if (seconds >= updateAt) {
        lastTimeStamp = millis();
    }
    return seconds;
}

int Timer::getIntervalInMinutes() {
    long diff = getInterval();
    int seconds = diff / 1000;
    if (seconds >= updateAt) {
        lastTimeStamp = millis();
    }
    return seconds / 60;
}
