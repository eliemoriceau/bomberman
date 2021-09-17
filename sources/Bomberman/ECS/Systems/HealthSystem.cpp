//
// Created by marin on 13/06/2021.
//

#include "HealthSystem.hpp"

void ECS::HealthSystem::damage(ECS::Entity entity, int damage) {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    auto health = ecsHandler->getComponent<ECS::HealthComponent>(entity);

    *(health.current_health) -= damage;
}

void ECS::HealthSystem::update() {
    ECS::ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    std::vector<ECS::Entity> to_deletes;

    for (auto &entity : _entities) {
        auto health = ecsHandler->getComponent<ECS::HealthComponent>(entity);
        if (*health.current_health <= 0 &&
            std::find(to_deletes.begin(), to_deletes.end(), entity) == to_deletes.end()) {
            to_deletes.push_back(entity);
        }
    }
    for (auto &entity : to_deletes) {
        ecsHandler->removeEntity(entity);
        PlayerManager::getInstance()->addPlayerToRemoveList(entity);
    }
}