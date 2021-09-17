//
// Created by marin on 10/06/2021.
//

#include "ColliderSystem.hpp"
#include "MoveComponent.hpp"
#include "MapManager.hpp"

void ECS::ColliderSystem::update() {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto &entity : _entities) {
        auto &transform = ecsHandler->getComponent<TransformComponent>(entity);
        if (!checkSamePosition(transform.position, transform.old_position)) {
            for (auto &entity1 : _entities) {
                if (entity != entity1) {
                    collision(transform, entity, entity1);
                }
            }
        }
    }
}

bool ECS::ColliderSystem::checkSamePosition(const std::shared_ptr<Raylib::Vector3> &v1,
                                            const std::shared_ptr<Raylib::Vector3> &v2) {
    return (v1->getX() == v2->getX() && v1->getY() == v2->getY() && v1->getZ() == v2->getZ());
}

void ECS::ColliderSystem::resetPosition(const ECS::TransformComponent &transform, ECS::TransformComponent &transform1) {
    if (!checkSamePosition(transform.position, transform.old_position)) {
        transform.position->setX(transform.old_position->getX());
        transform.position->setY(transform.old_position->getY());
        transform.position->setZ(transform.old_position->getZ());
    }
    if (!checkSamePosition(transform1.position, transform1.old_position)) {
        transform1.position->setX(transform1.old_position->getX());
        transform1.position->setY(transform1.old_position->getY());
        transform1.position->setZ(transform1.old_position->getZ());
    }
}

void
ECS::ColliderSystem::collision(const ECS::TransformComponent &transform, ECS::Entity entity1, ECS::Entity entity2) {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    auto &transform1 = ecsHandler->getComponent<ECS::TransformComponent>(entity2);

    if (checkSamePosition(transform.position, transform.old_position) &&
        checkSamePosition(transform1.position, transform1.old_position)) {
        return;
    }

    auto &collider = ecsHandler->getComponent<ECS::ColliderComponent>(entity1);
    auto &collider1 = ecsHandler->getComponent<ECS::ColliderComponent>(entity2);
    auto mapManager = MapManager::getInstance();

    if (collider.type == PLAYER_COLLIDER && collider1.type == PLAYER_COLLIDER)
        return;

    if (collider.type == PLAYER_COLLIDER && collider1.type == BOMB_COLLIDER &&
        checkSamePosition(mapManager->getGridPosition(transform.old_position),
                          mapManager->getGridPosition(transform1.position))) {
        return;
    }

    if ((collider.type == ECS::CUBE_COLLIDER || collider.type == ECS::PLAYER_COLLIDER ||
         collider.type == BOMB_COLLIDER) &&
        (collider1.type == ECS::CUBE_COLLIDER || collider1.type == ECS::PLAYER_COLLIDER ||
         collider1.type == BOMB_COLLIDER)) {
        if (CheckCollisionBoxes(
                Raylib::BoundingBox(transform.position->getVector(), collider.size->getVector()).getBox(),
                Raylib::BoundingBox(transform1.position->getVector(), collider1.size->getVector()).getBox())) {
            resetPosition(transform, transform1);
        }
    } else if (collider.type == ECS::SPHERE_COLLIDER && collider1.type == ECS::CUBE_COLLIDER) {
        if (CheckCollisionBoxSphere(
                Raylib::BoundingBox(transform1.position->getVector(), collider1.size->getVector()).getBox(),
                transform.position->getVector(), collider.size->getX())) {
            resetPosition(transform, transform1);
        }
    } else if (collider.type == ECS::SPHERE_COLLIDER && collider1.type == ECS::SPHERE_COLLIDER) {
        if (CheckCollisionSpheres(transform.position->getVector(), collider.size->getX(),
                                  transform1.position->getVector(), collider1.size->getX())) {
            resetPosition(transform, transform1);
        }
    } else if (collider.type == ECS::MODEL_COLLIDER && (collider1.type == ECS::SPHERE_COLLIDER ||
                                                        collider1.type == ECS::CUBE_COLLIDER))
        for (int y = 0; y < (int) collider.size->x; y++) {
            for (int x = 0; x < (int) collider.size->getZ(); x++) {
                if ((collider.colorsMap[y * (int) collider.size->getY() + x].r == 255) &&
                    // Collision: white pixel, only check R channel
                    (CheckCollisionCircleRec({transform1.position->getVector().x, transform1.position->getVector().y},
                                             collider1.size->x,
                                             {transform.position->x - 0.5f + (float) x * 1.0f,
                                              transform.position->y - 0.5f + (float) y * 1.0f, 1.0f, 1.0f}))) {
                    resetPosition(transform, transform1);
                }
            }
        }
}
