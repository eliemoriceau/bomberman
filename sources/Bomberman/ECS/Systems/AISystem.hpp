#pragma once

#include "System.hpp"
#include "Vector3.hpp"
#include <vector>
#include "TransformComponent.hpp"
#include "AIComponent.hpp"
#include <thread>

namespace ECS {
    class AISystem : public ECS::System {
    public:
        void target(ECS::TransformComponent comp, ECS::AIComponent ia);
        void updateIaPositionMap(ECS::TransformComponent transform);
        void update();

        int index;
    };
}