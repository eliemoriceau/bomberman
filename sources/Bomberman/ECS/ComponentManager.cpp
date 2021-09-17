#include "ComponentManager.hpp"

void ECS::ComponentManager::removedEntity(Entity entity) {
    for (auto &pair : _componentStores) {
        pair.second->entityDestroyed(entity);
    }
}