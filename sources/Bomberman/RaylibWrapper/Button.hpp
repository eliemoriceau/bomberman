/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Button
*/

#pragma once

#include "raylib.h"
#include <vector>
#include "Texture.hpp"
#include "Vector2.hpp"
#include "Text.hpp"

namespace Raylib {
    class Button {
    public:
        Button(const std::string &buttonFile1, const std::string &buttonFile2, const std::string &buttonFile3,
               const std::string &soundFile);

        ~Button() = default;

        void setButtonPosition(float x, float y);

        void manageButtonInterract();

        void drawButton();

        std::vector<std::shared_ptr<Raylib::Texture>> getTextureVector();

        Rectangle getSourceRec();

        ::Texture2D getTexture() const;

        float getX() const;

        void setX(float x);

        float getY() const;

        void setY(float y);

        float getWidth() const;

        void setWidth(float width);

        float getHeight() const;

        void setHeight(float height);

    private:
        float _x{};
        float _y{};
        float _width{};
        float _height{};
        ::Sound _buttonSound{};
        std::vector<std::shared_ptr<Raylib::Texture>> _textures;
        Rectangle _sourceRec{};
        Rectangle _btnBounds{};
        int _btnState;
        bool _btnAction;
        ::Vector2 _mousePoint{};
    };
}