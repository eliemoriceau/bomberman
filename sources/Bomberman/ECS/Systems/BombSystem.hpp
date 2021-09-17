//
// Created by marin on 12/06/2021.
//

#pragma once

#include "System.hpp"
#include "RenderComponent.hpp"
#include "ColliderComponent.hpp"
#include "ECSHandler.hpp"
#include "Timer.hpp"
#include "BombComponent.hpp"
#include "MapManager.hpp"
#include "PlayerManager.hpp"
#include "HealthSystem.hpp"
#include "BonusSystem.hpp"

namespace ECS {
    class BombSystem : public ECS::System {
    public:
        void update(std::shared_ptr<ECS::BonusSystem> bonus_system);

        void explode(std::shared_ptr<Raylib::Vector3> &pos, int range);

        void explodeAxe(std::shared_ptr<Raylib::Vector3> &pos, int range, std::pair<int, int> offset,
                        std::pair<int, int> axe);

        static void checkHitPlayer(const std::shared_ptr<Raylib::Vector3> &pos);

        static bool flash(Entity entity);

    private:
        std::shared_ptr<ECS::BonusSystem> _bonusSystem;

        void bombeAtPosition(std::shared_ptr<Raylib::Vector3> &pos);
    };
}