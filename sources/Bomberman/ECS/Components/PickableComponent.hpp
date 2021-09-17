/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include <memory>
#include "Vector3.hpp"

namespace ECS {
    enum PICKABLE_TYPE {
        PLAYER,
        BOMBER_UP,
        FIRE_UP,
        SPEED_UP,
    };
    struct PickableComponent {
        PICKABLE_TYPE type;
        std::shared_ptr<Raylib::Vector3> size;
    };
}
