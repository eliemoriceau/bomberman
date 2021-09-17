#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "Components/Component.hpp"
#include "System.hpp"
#include "Entity.hpp"
#include "Exception.hpp"

namespace ECS {
    class SystemManager {
    public:

        template<typename T>
        std::shared_ptr<T> registerSystem() {
            const char *typeName = typeid(T).name();
            if (_systems.find(typeName) == _systems.end()) {
                auto system = std::make_shared<T>();
                _systems.insert({typeName, system});
                return system;
            }
            throw ECS::Exception("this system is already registered");
        }

        template<typename T>
        void setUid(UID uid) {
            const char *typeName = typeid(T).name();

            if (_systems.find(typeName) != _systems.end()) {
                _systemUids.insert({typeName, uid});
            }
        }

        void entityRemoved(Entity);

        void entityUidChanged(Entity, UID);

    private:
        std::unordered_map<const char *, std::shared_ptr<System>> _systems{};
        std::unordered_map<const char *, ECS::UID> _systemUids{};
    };
}