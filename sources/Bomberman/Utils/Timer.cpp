/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Timer
*/

#include "Timer.hpp"

Timer::Timer() : _started(false) {
}

void Timer::start() {
    _startTime = std::chrono::system_clock::now();
    _started = true;
}

void Timer::stop() {
    _endTime = std::chrono::system_clock::now();
    _started = false;
}

double Timer::elapsedMilliseconds() {
    std::chrono::time_point<std::chrono::system_clock> endTime;

    if (_started)
        endTime = std::chrono::system_clock::now();
    else
        endTime = _endTime;
    return (std::chrono::duration_cast<std::chrono::milliseconds>(endTime - _startTime).count());
}

double Timer::elapsedSeconds() {
    return (elapsedMilliseconds() / 1000.0);
}