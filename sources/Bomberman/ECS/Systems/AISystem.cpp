//
// Created by marin on 20/06/2021.
//

#include "AISystem.hpp"
#include "ECSHandler.hpp"
#include "AIComponent.hpp"
#include "TransformComponent.hpp"
#include "MapManager.hpp"
#include "Text.hpp"
#include "Pathfinding.hpp"
#include "Input.hpp"
#include "PlayerManager.hpp"
#include "math.h"
#include <memory>
#include "Color.hpp"

void ECS::AISystem::updateIaPositionMap(ECS::TransformComponent transform)
{
    MapManager::getInstance()->setMapCoordPlayer(*transform.x, *transform.y,'O', transform.id);
    auto grid = MapManager::getInstance()->getGridPosition(transform.position);
    auto coords = MapManager::getInstance()->getArrayCoords(grid);

    MapManager::getInstance()->setMapCoordPlayer(coords.first, coords.second,transform.id, transform.id);
    transform.x = std::make_shared<int>(coords.first);
    transform.y = std::make_shared<int>(coords.second);
}

void  ECS::AISystem::target(ECS::TransformComponent comp, ECS::AIComponent ia) {
    if (ia._nextTarget->empty()) {
        if(*ia._fley == 1)
            *ia._fley = 0;

        if (*ia._attack == 1 && *ia._fley == 0 && ia._target != nullptr) {
            float dist = sqrt (pow(ia._target->x - comp.position->x, 2) + pow(ia._target->y - comp.position->y, 2) + pow(ia._target->z - comp.position->z, 2));
            if (dist < 2) {
                *ia._bombDrop = 1;
                ia._target = nullptr;
            }
        }
        return;
    }

    std::shared_ptr<Raylib::Vector3> currentWaypoint = ia._nextTarget->front();
    float dist = sqrt (pow(comp.position->x - currentWaypoint->x, 2) + pow(comp.position->y - currentWaypoint->y, 2) + pow(comp.position->z - currentWaypoint->z, 2));

    if (*ia._down != 0 || *ia._up != 0 || *ia._left != 0 || *ia._right != 0)
        return;

    if (dist > 0.2f) {
        if (currentWaypoint->x >= comp.position->x) {
            *ia._right = 1;
        } else {
            *ia._left = 1;
        }
        if (currentWaypoint->z >= comp.position->z) {
            *ia._down = 1;
        } else {
            *ia._up = 1;
        }
    }
    else
        ia._nextTarget->pop_front();
}



void attack_player(ECS::TransformComponent comp, ECS::TransformComponent enemy, ECS::AIComponent ai)
{
    std::list<std::shared_ptr<Raylib::Vector3>> list = Pathfinding::getInstance()->FindPath(comp.position, enemy.position);

    if (list.size() == 0)
        *ai._attack = 0;

    for (auto en : list) {
        ai._nextTarget->push_back(en);
    }
}

void fley_choice(ECS::TransformComponent comp, ECS::AIComponent ai)
{
    if (*ai._fley == 1)
        return;
    ai._nextTarget->clear();

    *ai._attack = 0;
    *ai._fley = 1;

    if (MapManager::getInstance()->checkAvailablePlace(comp.position)) {
        *ai._fley = 0;
        return;
    }

    auto new_pos = MapManager::getInstance()->getAvailablePlace(comp);
    std::list<std::shared_ptr<Raylib::Vector3>> list = Pathfinding::getInstance()->FindPath(comp.position, new_pos);

    if (list.size() == 0)
        *ai._fley = 0;

    for (auto en : list) {
        ai._nextTarget->push_back(en);
    }
}

void attack_choice(ECS::TransformComponent comp, ECS::AIComponent ai)
{
    auto ecsHandler = ECS::ECSHandler::getInstance();

    for (auto &entity : PlayerManager::getInstance()->getPlayers())
    {
        if (PlayerManager::getInstance()->isPlayerDead(entity))
            continue;

        auto enemy_comp = ecsHandler->getComponent<ECS::TransformComponent>(entity);

        if (enemy_comp.id == comp.id)
            continue;

        float dist = sqrt (pow(enemy_comp.position->x - comp.position->x, 2) + pow(enemy_comp.position->y - comp.position->y, 2) + pow(enemy_comp.position->z - comp.position->z, 2));
        if (dist < 3 && *ai._attack == 0) {
            attack_player(comp, enemy_comp, ai);
            ai._target = enemy_comp.position;
            *ai._fley = 1;
            *ai._attack = 1;
        }
    }
}

void ECS::AISystem::update() {
    auto ecsHandler = ECS::ECSHandler::getInstance();
    std::vector<std::thread> v;

    for (auto &entity : _entities) {
        auto iaComp = ecsHandler->getComponent<ECS::AIComponent>(entity);
        auto transformComp = ecsHandler->getComponent<ECS::TransformComponent>(entity);

        target(transformComp, iaComp);

        if (MapManager::getInstance()->checkMapType('E') == false && *iaComp._fley == 0) {
            attack_choice(transformComp, iaComp);
        } else {
            fley_choice(transformComp, iaComp);
        }
    }
}
