/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/
#pragma once

#include <Texture.hpp>
#include <Text.hpp>
#include "Button.hpp"

namespace ECS {
    enum RENDER_2D_TYPE {
        TEXTURE,
        TEXT,
        BUTTON
    };
    struct Render2dComponent {
        RENDER_2D_TYPE type;
        std::shared_ptr<Raylib::Texture> texture;
        std::shared_ptr<Raylib::Text> text;
        std::shared_ptr<Raylib::Button> button;
        std::shared_ptr<bool> enabled;
    };
}
