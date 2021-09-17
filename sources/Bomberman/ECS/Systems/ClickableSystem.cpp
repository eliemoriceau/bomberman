/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include <Render2dComponent.hpp>
#include "ClickableSystem.hpp"
#include "raylib.h"
#include "ECSHandler.hpp"
#include "ClickableComponent.hpp"

void ECS::ClickableSystem::update() {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    for (auto &entity : _entities) {
        auto clickable = ecsHandler->getComponent<ECS::ClickableComponent>(entity);
        auto render = ecsHandler->getComponent<ECS::Render2dComponent>(entity);

        Vector2 mousePos = ::GetMousePosition();
        if (::CheckCollisionPointRec(mousePos, clickable.recBox) &&
            ::IsMouseButtonReleased(::MOUSE_LEFT_BUTTON) && *render.enabled) {
            (clickable.callback)();
            break;
        }
    }
}
