/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "System.hpp"
#include "Input.hpp"
#include "ControllableComponents.hpp"
#include "RenderSystem.hpp"
#include "Game.hpp"
#include "EntityCreator.hpp"

namespace ECS {
    class ControllableSystem : public ECS::System {
    public:
        void update();

        void update_player(ECS::Entity entity);
        void update_ia(ECS::Entity entity);

        static void updatePlayerPositionMap(ECS::Entity entity);

        static void dropBomb(Raylib::Vector3 pos, int range);

        static void dropWall(Raylib::Vector3 pos);

        static bool isTimeToDrop(const ECS::ControllableComponent &controllable);
    };
}

