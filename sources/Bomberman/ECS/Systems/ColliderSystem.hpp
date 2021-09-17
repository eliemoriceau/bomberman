//
// Created by marin on 10/06/2021.
//

#pragma once

#include "System.hpp"
#include "RenderComponent.hpp"
#include "ColliderComponent.hpp"
#include "ECSHandler.hpp"

namespace ECS {
    class ColliderSystem : public ECS::System {
    public:
        void update();

        static void collision(const ECS::TransformComponent &transform, ECS::Entity entity1, ECS::Entity entity2);

        static void resetPosition(const ECS::TransformComponent &transform, ECS::TransformComponent &transform1);

        static bool
        checkSamePosition(const std::shared_ptr<Raylib::Vector3> &v1, const std::shared_ptr<Raylib::Vector3> &v2);
    };
}
