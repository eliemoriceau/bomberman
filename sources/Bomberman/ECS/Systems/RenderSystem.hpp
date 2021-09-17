#pragma once

#include "System.hpp"
#include "RenderComponent.hpp"

namespace ECS {
    class RenderSystem : public ECS::System {
    public:
        void update();

        static void drawCube(const RenderComponent &render, const TransformComponent &transform);

        static void drawSphere(const RenderComponent &render, const TransformComponent &transform);

        static void drawModel(const RenderComponent &render, const TransformComponent &transform);
    };
}