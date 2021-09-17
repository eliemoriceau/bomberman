//
// Created by marin on 10/06/2021.
//

#pragma once

#include <Vector3.hpp>
#include <memory>
#include "raylib.h"
#include "Object.hpp"

namespace ECS {
    struct TransformComponent {
        std::shared_ptr<Raylib::Vector3> position;
        std::shared_ptr<Raylib::Vector3> old_position;
        std::shared_ptr<Raylib::Vector3> rotation_axes;
        std::shared_ptr<int> x;
        std::shared_ptr<int> y;
        char id;
        char oldIdMap;
    };
}