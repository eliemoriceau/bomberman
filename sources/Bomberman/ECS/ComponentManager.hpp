#pragma once

#include <vector>
#include <typeinfo>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include "Components/Component.hpp"
#include "IComponentStore.hpp"
#include "Entity.hpp"
#include "Exception.hpp"

namespace ECS {
    class ComponentManager {
    public:

        template<typename T>
        void registerComponent() {
            std::string typeName = std::string(typeid(T).name());

            if (_componentTypes.find(typeName) == _componentTypes.end()) {
                _componentTypes.insert({typeName, _componentStoreCount});
                _componentStores.insert({typeName, std::make_shared<ComponentStore<T>>()});
                _componentStoreCount++;
            }
        }

        template<typename T>
        ECS::ComponentType getComponentType() {
            return _componentTypes.at(std::string(typeid(T).name()));
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            std::dynamic_pointer_cast<ComponentStore<T>>(
                    _componentStores.at(std::string(typeid(T).name())))->insertData(entity, component);
        }

        template<typename T>
        void removeComponent(Entity entity) {
            std::dynamic_pointer_cast<ComponentStore<T>>(
                    _componentStores.at(std::string(typeid(T).name())))->entityDestroyed(entity);
        }

        template<typename T>
        T &getComponent(Entity entity) {
            return std::dynamic_pointer_cast<ComponentStore<T>>(
                    _componentStores.at(std::string(typeid(T).name())))->getData(entity);
        }

        void removedEntity(Entity entity);

    private:
        std::unordered_map<std::string, ComponentType> _componentTypes{};
        std::unordered_map<std::string, std::shared_ptr<IComponentStore>> _componentStores{};
        size_t _componentStoreCount{};
    };
}