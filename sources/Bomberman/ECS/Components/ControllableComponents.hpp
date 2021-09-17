/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/
#pragma once

#include "Timer.hpp"
#include "raylib.h"
#include "Input.hpp"
#include "Sound.hpp"

namespace ECS {
    struct ControllableComponent {
        KeyboardKey up;
        KeyboardKey down;
        KeyboardKey left;
        KeyboardKey right;
        KeyboardKey bomb;
        KeyboardKey wall;
        std::shared_ptr<float> speed;
        std::shared_ptr<double> timerDrop;
        std::chrono::steady_clock::time_point timeLastDrop;
        std::shared_ptr<int> range;
        std::shared_ptr<Raylib::Sound> sound;
        std::shared_ptr<int> _ia;
    };
}
