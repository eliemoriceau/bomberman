/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "ECSHandler.hpp"
#include "TransformComponent.hpp"
#include "ControllableComponents.hpp"
#include "ControllableSystem.hpp"
#include "VectorUtils.hpp"
#include "AIComponent.hpp"

void ECS::ControllableSystem::updatePlayerPositionMap(ECS::Entity entity) {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    MapManager *map_manager = MapManager::getInstance();

    auto &transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);

    map_manager->setMapCoordPlayer(*transform.x, *transform.y, transform.oldIdMap, transform.id);
    auto grid = MapManager::getInstance()->getGridPosition(transform.position);
    auto coords = MapManager::getInstance()->getArrayCoords(grid);
    transform.oldIdMap = map_manager->getCellType(coords.first, coords.second);

    map_manager->setMapCoordPlayer(coords.first, coords.second, transform.id, transform.id);
    transform.x = std::make_shared<int>(coords.first);
    transform.y = std::make_shared<int>(coords.second);
}

void ECS::ControllableSystem::update_ia(ECS::Entity entity)
{
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    auto &ia = ecsHandler->getComponent<ECS::AIComponent>(entity);
    auto &transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);
    auto &renderer = ecsHandler->getComponent<ECS::RenderComponent>(entity);
    auto &controllable = ecsHandler->getComponent<ECS::ControllableComponent>(entity);

    transform.old_position->setX(transform.position->getX());
    transform.old_position->setY(transform.position->getY());
    transform.old_position->setZ(transform.position->getZ());


    if (*ia._bombDrop == 1 && isTimeToDrop(controllable)) {
        dropBomb(*transform.position, *controllable.range);
        transform.oldIdMap = 'E';
        controllable.timeLastDrop = std::chrono::steady_clock::now();
        *ia._bombDrop = 0;
        return;
    }
    if (*ia._up == 1) {
        updatePlayerPositionMap(entity);
        transform.position->z -= *controllable.speed;
        renderer.model->animModel();
        //transform.rotation_axes->z = -90;
        controllable.sound->playedSoundIf();
        *ia._up = 0;
        return;
    }
    if (*ia._down == 1) {
        updatePlayerPositionMap(entity);
        transform.position->z += *controllable.speed;
        renderer.model->animModel();
        //transform.rotation_axes->z = 90;
        controllable.sound->playedSoundIf();
        *ia._down = 0;
        return;
    }
    if (*ia._right == 1) {
        updatePlayerPositionMap(entity);
        transform.position->x += *controllable.speed;
        renderer.model->animModel();
        //transform.rotation_axes->z = 0;
        controllable.sound->playedSoundIf();
        *ia._right = 0;
        return;
    }
    if (*ia._left == 1) {
        updatePlayerPositionMap(entity);
        transform.position->x -= *controllable.speed;
        renderer.model->animModel();
        //transform.rotation_axes->z = 180;
        controllable.sound->playedSoundIf();
        *ia._left = 0;
        return;
    }

    if (*ia._left == 0 && *ia._right == 0 && *ia._up == 0 && *ia._down == 0) {
        renderer.model->UnAnimModel();
    }
}

void ECS::ControllableSystem::update_player(ECS::Entity entity)
{
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    auto &transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);
    auto &renderer = ecsHandler->getComponent<ECS::RenderComponent>(entity);

    transform.old_position->setX(transform.position->getX());
    transform.old_position->setY(transform.position->getY());
    transform.old_position->setZ(transform.position->getZ());

    auto &controllable = ecsHandler->getComponent<ECS::ControllableComponent>(entity);


    if (Raylib::Input::isKeyReleased(controllable.bomb) && isTimeToDrop(controllable)) {
        dropBomb(*transform.position, *controllable.range);
        transform.oldIdMap = 'E';
        controllable.timeLastDrop = std::chrono::steady_clock::now();
    } else if (Raylib::Input::isKeyReleased(controllable.wall) && isTimeToDrop(controllable)) {
        dropWall(*transform.position);
        controllable.timeLastDrop = std::chrono::steady_clock::now();
    }
    if (Raylib::Input::isKeyMaintain(controllable.up)) {
        updatePlayerPositionMap(entity);
        transform.position->z -= *controllable.speed;
        renderer.model->animModel();
        transform.rotation_axes->z = -90;
        controllable.sound->playedSoundIf();
    }
    if (Raylib::Input::isKeyMaintain(controllable.down)) {
        updatePlayerPositionMap(entity);
        transform.position->z += *controllable.speed;
        renderer.model->animModel();
        transform.rotation_axes->z = 90;
        controllable.sound->playedSoundIf();
    }
    if (Raylib::Input::isKeyMaintain(controllable.right)) {
        updatePlayerPositionMap(entity);
        transform.position->x += *controllable.speed;
        renderer.model->animModel();
        transform.rotation_axes->z = 0;
        controllable.sound->playedSoundIf();
    }
    if (Raylib::Input::isKeyMaintain(controllable.left)) {
        updatePlayerPositionMap(entity);
        transform.position->x -= *controllable.speed;
        renderer.model->animModel();
        transform.rotation_axes->z = 180;
        controllable.sound->playedSoundIf();
    }
    if (!Raylib::Input::isKeyMaintain(controllable.down) && !Raylib::Input::isKeyMaintain(controllable.up) &&
        !Raylib::Input::isKeyMaintain(controllable.right) && !Raylib::Input::isKeyMaintain(controllable.left)) {
        renderer.model->UnAnimModel();
    }
}
void ECS::ControllableSystem::update() {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto &entity : _entities) {

        auto &controllable = ecsHandler->getComponent<ECS::ControllableComponent>(entity);
        if (*controllable._ia == 1)
            update_ia(entity);
        else
            update_player(entity);
    }
}

void ECS::ControllableSystem::dropBomb(Raylib::Vector3 pos, int range) {
    auto mapManager = MapManager::getInstance();

    auto new_pos = newVector(pos.getX(), pos.getY(), pos.getZ());
    auto grid_pos = mapManager->getGridPosition(new_pos);
    auto coords = MapManager::getInstance()->getArrayCoords(grid_pos);

    EntityCreator::createBomb(new_pos, range);
    mapManager->setMapCoord(coords.first, coords.second, 'E');
}

void ECS::ControllableSystem::dropWall(Raylib::Vector3 pos) {
    auto new_pos = newVector(pos.getX(), pos.getY(), pos.getZ());
}

bool ECS::ControllableSystem::isTimeToDrop(const ECS::ControllableComponent &controllable) {
    std::chrono::steady_clock::time_point tmp = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
            tmp - controllable.timeLastDrop);

    if (time_span.count() >= *controllable.timerDrop) {
        return true;
    }
    return false;
}
