/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "raylib.h"
#include "Object.hpp"
#include "BoundingBox.hpp"
#include "Vector3.hpp"
#include "Object.hpp"

namespace ECS {
    enum COLLIDER_TYPE {
        SPHERE_COLLIDER,
        CUBE_COLLIDER,
        MODEL_COLLIDER,
        PLAYER_COLLIDER,
        BOMB_COLLIDER,
    };
    struct ColliderComponent {
        COLLIDER_TYPE type;
        std::shared_ptr<Raylib::Vector3> size;
        Color *colorsMap;
    };
}