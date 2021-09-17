#include "ECSHandler.hpp"

ECS::ECSHandler *ECS::ECSHandler::_instance = nullptr;

ECS::Entity ECS::ECSHandler::createEntity() {
    try {
        return _entityManager->createEntity();
    } catch (ECS::Exception &e) {
        std::cout << e.what() << std::endl;
        exit(0);
    }
}

void ECS::ECSHandler::removeEntity(ECS::Entity entity) {
    try {
        _entityManager->removeEntity(entity);
        _componentManager->removedEntity(entity);
        _systemManager->entityRemoved(entity);
    } catch (ECS::Exception &e) {
        std::cout << e.what() << std::endl;
        exit(0);
    }
}

ECS::ECSHandler::ECSHandler() : _entityManager(std::make_unique<EntityManager>()),
                                _componentManager(std::make_unique<ComponentManager>()),
                                _systemManager(std::make_unique<SystemManager>()) {
}

ECS::ECSHandler *ECS::ECSHandler::getInstance() {
    if (_instance == nullptr)
        _instance = new ECSHandler;
    return _instance;
}

void ECS::ECSHandler::clear() {
    _entityManager->clearEntities();
}