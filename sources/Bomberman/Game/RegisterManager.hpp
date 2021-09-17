//
// Created by marin on 14/06/2021.
//

#pragma once

#include "ECSHandler.hpp"
#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"
#include "ColliderSystem.hpp"
#include "ColliderComponent.hpp"
#include "BombSystem.hpp"
#include "BombComponent.hpp"
#include "ControllableSystem.hpp"
#include "ControllableComponents.hpp"
#include "BonusSystem.hpp"
#include "MoveSystem.hpp"
#include "MoveComponent.hpp"
#include "HealthSystem.hpp"
#include "HealthComponent.hpp"
#include "PickableSystem.hpp"
#include "ClickableComponent.hpp"
#include "ClickableSystem.hpp"
#include "Render2DSystem.hpp"
#include "Render2dComponent.hpp"

class RegisterManager {
public:
    ~RegisterManager() = default;

    static RegisterManager *getInstance();

    static void registerComponents();

    static void registerUids();

private:
    RegisterManager() = default;

    static RegisterManager *_instance;
};
