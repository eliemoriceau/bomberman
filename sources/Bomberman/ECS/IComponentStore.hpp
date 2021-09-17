#pragma once

#include <unordered_map>
#include "Entity.hpp"
#include "Exception.hpp"

namespace ECS {
    class IComponentStore {
    public:
        virtual ~IComponentStore() = default;

        virtual void entityDestroyed(Entity entity) = 0;
    };


    template<typename T>
    class ComponentStore : public IComponentStore {
    public:
        void insertData(ECS::Entity entity, T component) {
            if (entity <= MAX_ENTITIES) {
                _components.at(entity) = component;
            }
        }

        T &getData(Entity entity) {
            return _components.at(entity);
        }

        void entityDestroyed(ECS::Entity entity) override {
            if (entity <= MAX_ENTITIES) {
                _components.at(entity) = {};
            }
        }

    private:
        std::array<T, MAX_ENTITIES> _components{};
    };
}