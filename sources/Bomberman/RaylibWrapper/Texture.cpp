/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Espace de travail)
** File description:
** Texture
*/

#include "Texture.hpp"

#include <utility>

Raylib::Texture::Texture(std::string filename, int posX, int posY, Color tint) : _filename(std::move(filename)),
                                                                                 _posX(posX),
                                                                                 _posY(posY), _tint(tint) {
    loadTexture();
}

Raylib::Texture::~Texture() {
    UnloadTexture(_texture);
}

int Raylib::Texture::getPosX() const {
    return _posX;
}

void Raylib::Texture::setPosX(int posX) {
    _posX = posX;
}

int Raylib::Texture::getPosY() const {
    return _posY;
}

void Raylib::Texture::setPosY(int posY) {
    _posY = posY;
}

void Raylib::Texture::loadTexture() {
    _texture = LoadTexture(_filename.c_str());
}

void Raylib::Texture::setColor(::Color tint) {
    _tint = tint;
}

::Color Raylib::Texture::getColor() {
    return _tint;
}

void Raylib::Texture::drawTexture() {
    DrawTexture(_texture, _posX, _posY, _tint);
}

const Texture2D &Raylib::Texture::getTexture() const {
    return _texture;
}
