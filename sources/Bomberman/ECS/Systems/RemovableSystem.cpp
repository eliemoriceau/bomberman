/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "ECSHandler.hpp"
#include "RemovableComponent.hpp"
#include "RemovableSystem.hpp"

void ECS::RemovableSystem::update() {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    std::vector<ECS::Entity> to_delete;

    for (auto &entity : _entities) {
        auto &remove = ecsHandler->getComponent<ECS::RemovableComponent>(entity);
        if (remove.timer->elapsedMilliseconds() > remove.time) {
            to_delete.push_back(entity);
            remove.timer->start();
            break;
        }
    }
    for (auto entity : to_delete) {
        ecsHandler->removeEntity(entity);
    }
}
