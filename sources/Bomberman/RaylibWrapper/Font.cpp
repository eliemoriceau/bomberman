/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "Font.hpp"

Raylib::Font::Font(std::string fontPath) : _fontPath(std::move(fontPath)), _font(LoadFont(_fontPath.c_str())) {
}

Raylib::Font::~Font() {
    UnloadFont(_font);
}

const std::string &Raylib::Font::getFontPath() const {
    return _fontPath;
}

void Raylib::Font::setFontPath(const std::string &fontPath) {
    UnloadFont(_font);
    _fontPath = fontPath;
    LoadFont(_fontPath.c_str());
}

Font &Raylib::Font::getFont() {
    return _font;
}

void Raylib::Font::setFont(const ::Font &font) {
    _font = font;
}
