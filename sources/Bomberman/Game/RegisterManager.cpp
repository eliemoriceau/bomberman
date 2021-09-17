//
// Created by marin on 14/06/2021.
//

#include <RemovableComponent.hpp>
#include <RemovableSystem.hpp>
#include "RegisterManager.hpp"
#include "AIComponent.hpp"
#include "AISystem.hpp"

RegisterManager *RegisterManager::_instance = nullptr;

RegisterManager *RegisterManager::getInstance() {
    if (_instance == nullptr)
        _instance = new RegisterManager();
    return _instance;
}

void RegisterManager::registerUids() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    ECS::UID uid;
    uid.set(ecsHandler->getComponentType<ECS::RenderComponent>());
    uid.set(ecsHandler->getComponentType<ECS::TransformComponent>());
    ecsHandler->setUid<ECS::RenderSystem>(uid);

    ECS::UID uid1;
    uid1.set(ecsHandler->getComponentType<ECS::ColliderComponent>());
    ecsHandler->setUid<ECS::ColliderSystem>(uid1);

    ECS::UID uid2;
    uid2.set(ecsHandler->getComponentType<ECS::MoveComponent>());
    ecsHandler->setUid<ECS::MoveSystem>(uid2);

    ECS::UID uid3;
    uid3.set(ecsHandler->getComponentType<ECS::ControllableComponent>());
    ecsHandler->setUid<ECS::ControllableSystem>(uid3);

    ECS::UID uid4;
    uid4.set(ecsHandler->getComponentType<ECS::BombComponent>());
    ecsHandler->setUid<ECS::BombSystem>(uid4);


    ECS::UID uid5;
    uid5.set(ecsHandler->getComponentType<ECS::HealthComponent>());
    ecsHandler->setUid<ECS::HealthSystem>(uid5);

    ECS::UID uidPickable;
    uidPickable.set(ecsHandler->getComponentType<ECS::PickableComponent>());
    ecsHandler->setUid<ECS::PickableSystem>(uidPickable);


    ECS::UID uidCliq;
    uidCliq.set(ecsHandler->getComponentType<ECS::ClickableComponent>());
    ecsHandler->setUid<ECS::ClickableSystem>(uidCliq);

    ECS::UID uiR;
    uiR.set(ecsHandler->getComponentType<ECS::Render2dComponent>());
    ecsHandler->setUid<ECS::Render2dSystem>(uiR);

    ECS::UID uidRemovable;
    uidRemovable.set(ecsHandler->getComponentType<ECS::RemovableComponent>());
    ecsHandler->setUid<ECS::RemovableSystem>(uidRemovable);

    ECS::UID uiIA;
    uiIA.set(ecsHandler->getComponentType<ECS::AIComponent>());
    ecsHandler->setUid<ECS::AISystem>(uiIA);

}

void RegisterManager::registerComponents() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    ecsHandler->registerComponent<ECS::RenderComponent>();
    ecsHandler->registerComponent<ECS::TransformComponent>();
    ecsHandler->registerComponent<ECS::ColliderComponent>();
    ecsHandler->registerComponent<ECS::MoveComponent>();
    ecsHandler->registerComponent<ECS::ControllableComponent>();
    ecsHandler->registerComponent<ECS::BombComponent>();
    ecsHandler->registerComponent<ECS::HealthComponent>();
    ecsHandler->registerComponent<ECS::PickableComponent>();
    ecsHandler->registerComponent<ECS::ClickableComponent>();
    ecsHandler->registerComponent<ECS::Render2dComponent>();
    ecsHandler->registerComponent<ECS::RemovableComponent>();
    ecsHandler->registerComponent<ECS::AIComponent>();
}