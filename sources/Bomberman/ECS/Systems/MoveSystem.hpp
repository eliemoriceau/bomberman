/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "System.hpp"
#include "MoveComponent.hpp"

namespace ECS {
    class MoveSystem : public ECS::System {
    public:
        void update();
    };
}

