//
// Created by marin on 13/06/2021.
//

#pragma once

#include <Vector3.hpp>
#include <memory>
#include "raylib.h"
#include "Object.hpp"

namespace ECS {
    struct HealthComponent {
        std::shared_ptr<int> current_health;
    };
}
