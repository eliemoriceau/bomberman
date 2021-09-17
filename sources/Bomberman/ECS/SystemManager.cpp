#include "SystemManager.hpp"

void ECS::SystemManager::entityRemoved(ECS::Entity entity) {
    for (auto const &pair : _systems) {
        auto const &system = pair.second;
        system->_entities.remove(entity);
    }
}

void ECS::SystemManager::entityUidChanged(ECS::Entity entity, const ECS::UID uid) {

    for (auto const &pair : _systems) {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = _systemUids[type];

        if ((uid & systemSignature) == systemSignature) {
            system->_entities.push_back(entity);
        } else {
            system->_entities.remove(entity);
        }
    }
}
