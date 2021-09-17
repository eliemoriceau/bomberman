#pragma once

#include <deque>
#include <array>
#include "Entity.hpp"
#include "Components/Component.hpp"
#include "Exception.hpp"
#include <algorithm>

namespace ECS {
    class EntityManager {
    public:
        EntityManager();

        ~EntityManager() = default;

        Entity createEntity();

        void removeEntity(Entity entity);

        void clearEntities();

        void setUid(Entity, UID);

        UID getUid(Entity entity);

    private:
        std::deque<Entity> _unusedEntities;
        std::array<UID, MAX_ENTITIES> _entityUids;
        size_t _entityCount{};
    };
}