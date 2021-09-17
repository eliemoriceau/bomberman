/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "PickableComponent.hpp"
#include "ECSHandler.hpp"
#include "PickableSystem.hpp"
#include "Game.hpp"

void ECS::PickableSystem::update() {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    MapManager *map_manager = MapManager::getInstance();


    for (auto &player : _entities) {
        auto &pickablePlayer = ecsHandler->getComponent<PickableComponent>(player);
        if (pickablePlayer.type == ECS::PICKABLE_TYPE::PLAYER) {
            for (auto &bonus : _entities) {
                auto &pickableBonus = ecsHandler->getComponent<PickableComponent>(bonus);
                auto &transformBonus = ecsHandler->getComponent<TransformComponent>(bonus);
                auto &transformPlayer = ecsHandler->getComponent<TransformComponent>(player);


                if (pickableBonus.type != ECS::PICKABLE_TYPE::PLAYER &&
                    collision(transformPlayer, transformBonus, pickablePlayer, pickableBonus)) {
                    auto gridPos = map_manager->getGridPosition(transformPlayer.position);
                    auto coords = MapManager::getInstance()->getArrayCoords(gridPos);
                    switch (pickableBonus.type) {
                        case BOMBER_UP:
                            bombUp(ecsHandler, player);
                            break;
                        case FIRE_UP:
                            fireUp(ecsHandler, player);
                            break;
                        case SPEED_UP:
                            speedUp(ecsHandler, player);
                            break;
                        default:
                            break;
                    }
                    map_manager->setMapCoord(coords.first, coords.second, 'O');
                    map_manager->removeBonus(bonus);
                    return;
                }
            }
        }
    }
}

void ECS::PickableSystem::bombUp(ECS::ECSHandler *ecsHandler, ECS::Entity player) {
    auto controllable = ecsHandler->getComponent<ControllableComponent>(player);
    auto &transformPlayer = ecsHandler->getComponent<TransformComponent>(player);

    HUD::getInstance()->updateHubPropertiesUp(PlayerManager::getIndexByID(transformPlayer.id));

    *controllable.timerDrop -= 0.1;
}

void ECS::PickableSystem::fireUp(ECS::ECSHandler *ecsHandler, ECS::Entity player) {
    auto bomb = ecsHandler->getComponent<ControllableComponent>(player);
    auto &transformPlayer = ecsHandler->getComponent<TransformComponent>(player);

    HUD::getInstance()->updateHubPropertiesFire(PlayerManager::getIndexByID(transformPlayer.id));

    *bomb.range += 1;
}

void ECS::PickableSystem::speedUp(ECS::ECSHandler *ecsHandler, ECS::Entity player) {
    auto controllable = ecsHandler->getComponent<ControllableComponent>(player);
    auto &transformPlayer = ecsHandler->getComponent<TransformComponent>(player);

    HUD::getInstance()->updateHubPropertiesSpeed(PlayerManager::getIndexByID(transformPlayer.id));

    *controllable.speed += 0.005;
}

bool ECS::PickableSystem::collision(const ECS::TransformComponent &transformPlayer,
                                    const ECS::TransformComponent &transformBonus,
                                    const ECS::PickableComponent &pickablePlayer,
                                    const ECS::PickableComponent &pickableBonus) {
    MapManager *map_manager = MapManager::getInstance();
    if (map_manager->getGridPosition(transformPlayer.position) !=
        map_manager->getGridPosition(transformBonus.position)) {
        bool res = CheckCollisionBoxes(
                Raylib::BoundingBox(map_manager->getGridPosition(transformPlayer.position)->getVector(),
                                    pickablePlayer.size->getVector()).getBox(),
                Raylib::BoundingBox(map_manager->getGridPosition(transformBonus.position)->getVector(),
                                    pickableBonus.size->getVector()).getBox());
        return res;
    }
    return false;
}

