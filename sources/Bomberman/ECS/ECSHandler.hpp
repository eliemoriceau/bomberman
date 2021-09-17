#pragma once

#include <iostream>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "Entity.hpp"
#include "Exception.hpp"

namespace ECS {
    class ECSHandler {
    public:
        static ECSHandler *getInstance();

        template<typename T>
        void addComponent(ECS::Entity entity, T component) {
            try {
                _componentManager->addComponent(entity, component);

                UID uid = _entityManager->getUid(entity);
                uid.set(_componentManager->getComponentType<T>(), true);
                _entityManager->setUid(entity, uid);
                _systemManager->entityUidChanged(entity, uid);
            } catch (ECS::Exception &e) {
                std::cout << e.what() << std::endl;
                exit(0);
            }
        }

        template<typename T>
        T &getComponent(ECS::Entity entity) {
            return _componentManager->getComponent<T>(entity);
        }

        Entity createEntity();

        void removeEntity(Entity);

        template<typename T>
        void registerComponent() {
            try {
                _componentManager->registerComponent<T>();
            } catch (ECS::Exception &e) {
                std::cout << e.what() << std::endl;
                exit(0);
            }
        }

        template<typename T>
        ECS::ComponentType getComponentType() {
            try {
                return _componentManager->getComponentType<T>();
            } catch (ECS::Exception &e) {
                std::cout << e.what() << std::endl;
                exit(0);
            }
        }

        template<typename T>
        std::shared_ptr<T> registerSystem() {
            try {
                return _systemManager->registerSystem<T>();
            } catch (ECS::Exception &e) {
                std::cout << e.what() << std::endl;
                exit(0);
            }
        }

        template<typename T>
        void setUid(ECS::UID uid) {
            try {
                _systemManager->setUid<T>(uid);
            } catch (ECS::Exception &e) {
                std::cout << e.what() << std::endl;
                exit(0);
            }
        }

        void clear();

    private:
        ECSHandler();

        static ECSHandler *_instance;
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<SystemManager> _systemManager;
    };
}