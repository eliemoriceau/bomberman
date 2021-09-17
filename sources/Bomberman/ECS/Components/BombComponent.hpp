//
// Created by marin on 12/06/2021.
//

#pragma once

#include <Vector3.hpp>
#include <memory>
#include <DefineResources.hpp>
#include <Sound.hpp>
#include "raylib.h"
#include "Timer.hpp"

namespace ECS {
    struct BombComponent {
        int time;
        std::shared_ptr<Timer> timer;
        bool flash;
        int max_flash;
        int count_flash;
        int range;
        std::shared_ptr<Raylib::Sound> explosion;
        std::shared_ptr<Raylib::Sound> wick;
    };
}
