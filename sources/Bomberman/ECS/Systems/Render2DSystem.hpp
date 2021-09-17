/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "System.hpp"
#include "Render2dComponent.hpp"
#include "TransformComponent.hpp"

namespace ECS {
    class Render2dSystem : public System {
    public:
        void update();

        static void drawText(const ECS::Render2dComponent &render, const TransformComponent &transform);

        static void drawTexture(const ECS::Render2dComponent &render, const TransformComponent &transform);

        static void drawButton(const ECS::Render2dComponent &render, const TransformComponent &transform);
    };
}
