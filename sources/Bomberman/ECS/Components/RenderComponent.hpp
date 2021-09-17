#pragma once

#include <Texture.hpp>
#include <memory>
#include "raylib.h"
#include "Object.hpp"
#include "TransformComponent.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Color.hpp"

namespace ECS {
    enum RENDER_TYPE {
        SPHERE,
        CUBE,
        MODEL,
        NONE
    };
    struct RenderComponent {
        RENDER_TYPE renderType;
        std::shared_ptr<Raylib::Vector3> size;
        std::shared_ptr<Raylib::Model> model;
        std::shared_ptr<Raylib::ColorRGB> color;
        std::shared_ptr<Raylib::Texture> texture;
    };
}