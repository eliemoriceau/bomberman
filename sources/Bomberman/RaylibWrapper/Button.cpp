/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Button
*/

#include "Button.hpp"
#include "EntityCreator.hpp"
#include "AssetManager.hpp"

Raylib::Button::Button(const std::string &buttonFile1, const std::string &buttonFile2, const std::string &buttonFile3,
                       const std::string &soundFile) {
    auto asset = AssetManager::getInstance();

    _textures.push_back(asset->getTexture(buttonFile1));
    _textures.push_back(asset->getTexture(buttonFile2));
    _textures.push_back(asset->getTexture(buttonFile3));
    _buttonSound = asset->getSound(soundFile)->getSound();
    _btnState = 0;
    _btnAction = false;
    _mousePoint = {0.0f, 0.0f};

}

void Raylib::Button::setButtonPosition(float x, float y) {
    _x = x;
    _y = y;

    _sourceRec = {0, 0, (float) _textures[0]->getTexture().width, (float) _textures[0]->getTexture().height};
    _btnBounds = {_x, _y, (float) _textures[0]->getTexture().width, (float) _textures[0]->getTexture().height};
}

void Raylib::Button::manageButtonInterract() {
    _mousePoint = ::GetMousePosition();
    _btnAction = false;

    if (::CheckCollisionPointRec(_mousePoint, _btnBounds)) {
        if (::IsMouseButtonDown(::MOUSE_LEFT_BUTTON))
            _btnState = 2;
        else
            _btnState = 1;
        if (::IsMouseButtonReleased(::MOUSE_LEFT_BUTTON))
            _btnAction = true;
    } else
        _btnState = 0;
    if (_btnAction)
        ::PlaySound(_buttonSound);
}

void Raylib::Button::drawButton() {
    if (_btnState != -1)
        ::DrawTextureRec(_textures[_btnState]->getTexture(), _sourceRec, {_btnBounds.x, _btnBounds.y}, WHITE);
}

std::vector<std::shared_ptr<Raylib::Texture>> Raylib::Button::getTextureVector() {
    return _textures;
}


Rectangle Raylib::Button::getSourceRec() {
    return (_sourceRec);
}

::Texture2D Raylib::Button::getTexture() const {
    return _textures.at(_btnState)->getTexture();
}

float Raylib::Button::getX() const {
    return _x;
}

void Raylib::Button::setX(float x) {
    _x = x;
}

float Raylib::Button::getY() const {
    return _y;
}

void Raylib::Button::setY(float y) {
    _y = y;
}

float Raylib::Button::getWidth() const {
    return _width;
}

void Raylib::Button::setWidth(float width) {
    _width = width;
}

float Raylib::Button::getHeight() const {
    return _height;
}

void Raylib::Button::setHeight(float height) {
    _height = height;
}