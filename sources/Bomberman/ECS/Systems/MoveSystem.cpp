/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "MoveSystem.hpp"
#include "ECSHandler.hpp"
#include "TransformComponent.hpp"

void ECS::MoveSystem::update() {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto &entity : _entities) {
        auto transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);
        transform.old_position->setX(transform.position->getX());
        transform.old_position->setY(transform.position->getY());
        transform.old_position->setZ(transform.position->getZ());

    }
}
