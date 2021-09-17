/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "Text.hpp"

#include <utility>

Raylib::Text::Text(std::string text, std::shared_ptr<Raylib::Font> font, const Vector2 &pos, int size)
        : _text(std::move(text)),
          _font(std::move(font)), _pos(pos),
          _size((float) size), _color(WHITE) {
}

void Raylib::Text::drawtext() {
    DrawTextEx(_font->getFont(), _text.c_str(), {_pos._x, _pos._y}, _size, _size, _color);
}

const std::string &Raylib::Text::getText() const {
    return _text;
}

void Raylib::Text::setText(const std::string &text) {
    _text = text;
}

const Raylib::Vector2 &Raylib::Text::getPos() const {
    return _pos;
}

void Raylib::Text::setPos(const Vector2 &pos) {
    _pos = pos;
}

void Raylib::Text::setPos(float posX, float posY) {
    _pos._x = posX;
    _pos._y = posY;
}

void Raylib::Text::setPosX(float posX) {
    _pos._x = posX;
}

void Raylib::Text::setPosY(float posY) {
    _pos._y = posY;
}

float Raylib::Text::getSize() const {
    return _size;
}

void Raylib::Text::setSize(float size) {
    _size = size;
}

const Color &Raylib::Text::getColor() const {
    return _color;
}

void Raylib::Text::setColor(const Color &color) {
    _color = color;
}

const std::shared_ptr<Raylib::Font> &Raylib::Text::getFont() const {
    return _font;
}

void Raylib::Text::setFont(const std::shared_ptr<Raylib::Font> &font) {
    _font = font;
}

