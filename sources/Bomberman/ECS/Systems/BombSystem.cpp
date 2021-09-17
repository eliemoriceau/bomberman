//
// Created by marin on 12/06/2021.
//

#include "BombSystem.hpp"
#include <utility>

bool ECS::BombSystem::flash(Entity entity) {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    auto &render = ecsHandler->getComponent<RenderComponent>(entity);
    auto &bomb = ecsHandler->getComponent<BombComponent>(entity);

    if (bomb.timer->elapsedMilliseconds() > 100) {
        Raylib::Vector3 scale = render.model->getScale();
        if (bomb.count_flash < 5)
            render.model->setScale(Raylib::Vector3(scale.x - 0.1f, scale.y - 0.1f, scale.z - 0.1f));
        else
            render.model->setScale(Raylib::Vector3(scale.x + 0.1f, scale.y + 0.1f, scale.z + 0.1f));
        bomb.timer->start();
        if (bomb.count_flash == bomb.max_flash) {
            render.model->setScale(Raylib::Vector3(1, 1, 1));
            return true;
        }
        bomb.count_flash++;
    }
    return (false);
}

void ECS::BombSystem::checkHitPlayer(const std::shared_ptr<Raylib::Vector3> &pos) {
    for (auto &entity : PlayerManager::getInstance()->getPlayers()) {
        if (!PlayerManager::getInstance()->isPlayerDead(entity)) {
            ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
            auto &transform = ecsHandler->getComponent<TransformComponent>(entity);
            auto gridPosPlayer = MapManager::getInstance()->getGridPosition(transform.position);
            if (gridPosPlayer->x == pos->x && gridPosPlayer->z == pos->z) {
                auto coords = MapManager::getInstance()->getArrayCoords(gridPosPlayer);
                HealthSystem::damage(entity, 1);
                MapManager::getInstance()->setMapCoordPlayer(coords.first, coords.second, 'O', transform.id);
            }
        }
    }
}

void ECS::BombSystem::explodeAxe(std::shared_ptr<Raylib::Vector3> &pos, int range, std::pair<int, int> offset,
                                 std::pair<int, int> axe) {
    MapManager *map_manager = MapManager::getInstance();
    auto grid_posStart = map_manager->getGridPosition(pos);
    auto coordsStart = MapManager::getInstance()->getArrayCoords(grid_posStart);

    for (int x = offset.first; x < offset.second; x++) {
        auto grid_pos = map_manager->getGridPosition(
                newVector(pos->x + (x * axe.first), pos->y, pos->z + (x * axe.second)));
        auto coords = MapManager::getInstance()->getArrayCoords(grid_pos);

        if (map_manager->checkCellType(coords.first, coords.second, 'B')) {
            map_manager->setMapCoord(coords.first, coords.second, 'O');
            map_manager->deleteBreakableWallAtPosition(grid_pos);
            _bonusSystem->drop(grid_pos);
        } else if (map_manager->checkCellType(coords.first, coords.second, 'P')) {
            map_manager->setMapCoord(coords.first, coords.second, 'O');
            map_manager->deleteBonusAtPosition(grid_pos);
        }
        if (map_manager->checkCellType(coords.first, coords.second, 'E') &&
            (coords.first != coordsStart.first || coords.second != coordsStart.second)) {
            map_manager->setMapCoord(coords.first, coords.second, 'O');
            bombeAtPosition(grid_pos);
        }
        if (map_manager->checkCellType(coords.first, coords.second, 'U') ||
            map_manager->checkCellType(coords.first, coords.second, 'X')) {
            break;
        }
        EntityCreator::createExplosion(newVector(grid_pos->getX(), grid_pos->getY(), grid_pos->getZ()));
        checkHitPlayer(grid_pos);
    }
}

void ECS::BombSystem::explode(std::shared_ptr<Raylib::Vector3> &pos, int range) {
    MapManager *map_manager = MapManager::getInstance();

    auto grid_pos = map_manager->getGridPosition(pos);
    auto coords = MapManager::getInstance()->getArrayCoords(grid_pos);
    map_manager->setMapCoord(coords.first, coords.second, 'O');

    explodeAxe(pos, range, {0, range}, {1, 0});
    explodeAxe(pos, range, {0, range}, {-1, 0});
    explodeAxe(pos, range, {0, range}, {0, 1});
    explodeAxe(pos, range, {0, range}, {0, -1});
}

void ECS::BombSystem::update(std::shared_ptr<ECS::BonusSystem> bonus_system) {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    auto mapManager = MapManager::getInstance();
    auto bombList = mapManager->getBombe();

    if (_bonusSystem == nullptr)
        _bonusSystem = std::move(bonus_system);

    for (auto &entity : _entities) {
        auto &bomb = ecsHandler->getComponent<BombComponent>(entity);
        bomb.wick->playedSoundIf();

        if (bomb.timer->elapsedSeconds() > bomb.time && !bomb.flash) {
            bomb.flash = true;
        }
        if (bomb.flash) {
            if (flash(entity)) {
                auto &transform = ecsHandler->getComponent<TransformComponent>(entity);
                bombList.remove(entity);
                bomb.wick->stopSound();
                bomb.explosion->playSound();

                if (std::find(bombList.begin(), bombList.end(), entity) == bombList.end())
                    explode(transform.position, bomb.range + 1);
                mapManager->removeBomb(entity);
                break;
            }
        }
    }
}

void ECS::BombSystem::bombeAtPosition(std::shared_ptr<Raylib::Vector3> &pos) {
    auto mapManager = MapManager::getInstance();
    auto bombList = mapManager->getBombe();

    for (auto entity : bombList) {
        ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
        auto transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);

        if (transform.position == nullptr) {
            continue;
        }
        if (transform.position->x == pos->x && transform.position->z == pos->z) {
            auto range = ecsHandler->getComponent<ECS::BombComponent>(entity).range;
            if (std::find(bombList.begin(), bombList.end(), entity) != bombList.end()) {
                explode(pos, range + 1);
            }
            mapManager->removeBomb(entity);
            break;
        }
    }
}