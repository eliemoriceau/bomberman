#include <algorithm>
#include "EntityManager.hpp"
#include "ECSHandler.hpp"

ECS::EntityManager::EntityManager() {
    for (size_t i = 0; i < MAX_ENTITIES; i++) {
        _unusedEntities.push_back(i);
    }
}

ECS::Entity ECS::EntityManager::createEntity() {

    if (_entityCount < MAX_ENTITIES) {
        Entity newEntity = _unusedEntities.front();
        _unusedEntities.pop_front();
        _entityCount++;
        return newEntity;
    }
    return INVALID_ENTITY;
}

void ECS::EntityManager::removeEntity(ECS::Entity entity) {
    if (entity < MAX_ENTITIES) {
        _entityUids.at(entity).reset();
        _unusedEntities.push_back(entity);
        _entityCount--;
    }
}

void ECS::EntityManager::setUid(ECS::Entity entity, const ECS::UID uid) {
    if (entity < MAX_ENTITIES) {
        _entityUids.at(entity) = uid;
    }
}

ECS::UID ECS::EntityManager::getUid(ECS::Entity entity) {
    return _entityUids.at(entity);
}

void ECS::EntityManager::clearEntities() {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();

    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (std::find(_unusedEntities.begin(), _unusedEntities.end(), i) == _unusedEntities.end())
            ecsHandler->removeEntity(i);
    }
}