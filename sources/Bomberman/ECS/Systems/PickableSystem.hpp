/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "System.hpp"
#include "TransformComponent.hpp"

namespace ECS {
    class PickableSystem : public System {
    public:
        void update();

        static bool
        collision(const ECS::TransformComponent &transformPlayer, const ECS::TransformComponent &transformBonus,
                  const ECS::PickableComponent &pickablePlayer, const ECS::PickableComponent &pickableBonus);

        static void bombUp(ECS::ECSHandler *ecsHandler, ECS::Entity player);

        static void fireUp(ECS::ECSHandler *ecsHandler, ECS::Entity player);

        static void speedUp(ECS::ECSHandler *ecsHandler, ECS::Entity player);
    };
}

