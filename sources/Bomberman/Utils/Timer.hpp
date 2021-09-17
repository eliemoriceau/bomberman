/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Timer
*/

#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

class Timer {
public:
    Timer();

    ~Timer() = default;

    void start();

    void stop();

    double elapsedMilliseconds();

    double elapsedSeconds();

protected:
private:
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    std::chrono::time_point<std::chrono::system_clock> _endTime;
    bool _started;
};