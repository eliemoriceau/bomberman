/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include <memory>
#include <Vector3.hpp>
#include "raylib.h"

namespace ECS {
    struct MoveComponent {
        std::shared_ptr<Raylib::Vector3> speed;
    };
}