//
// Created by marin on 13/06/2021.
//

#pragma once

#include "System.hpp"
#include "ECSHandler.hpp"
#include "HealthComponent.hpp"
#include "PlayerManager.hpp"
#include <algorithm>

namespace ECS {
    class HealthSystem : public ECS::System {
    public:
        void update();

        static void damage(ECS::Entity entity, int damage);
    };
}
