/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include <string>
#include <memory>
#include "raylib.h"
#include "Font.hpp"
#include "Vector2.hpp"
#include <memory>

namespace Raylib {
    class Text {
    public:
        Text(std::string text, std::shared_ptr<Raylib::Font> font, const Vector2 &pos, int size);

        ~Text() = default;

        void drawtext();

        const std::string &getText() const;

        void setText(const std::string &text);

        const Vector2 &getPos() const;

        void setPos(const Vector2 &pos);

        void setPos(float posX, float posY);

        void setPosX(float posX);

        void setPosY(float posY);

        float getSize() const;

        void setSize(float size);

        const ::Color &getColor() const;

        void setColor(const ::Color &color);

    private:
        std::string _text;
        Raylib::Vector2 _pos;
        float _size;
        ::Color _color{};
        std::shared_ptr<Raylib::Font> _font;
    public:
        const std::shared_ptr<Raylib::Font> &getFont() const;

        void setFont(const std::shared_ptr<Raylib::Font> &font);
    };
}
