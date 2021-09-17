/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "Vector2.hpp"

Raylib::Vector2::Vector2(float x, float y) : _x(x), _y(y) {

}

Raylib::Vector2::Vector2(const Vector2 &other) {
    _x = other._x;
    _y = other._y;
}

void Raylib::Vector2::add(const Raylib::Vector2 &add) {
    _x += add._x;
    _y += add._y;
}

float Raylib::Vector2::getX() const {
    return _x;
}

float Raylib::Vector2::getY() const {
    return _y;
}

void Raylib::Vector2::setX(float value) {
    _x = value;
}

void Raylib::Vector2::setY(float value) {
    _y = value;
}

void Raylib::Vector2::set(float x, float y) {
    setX(x);
    setY(y);
}

Raylib::Vector2 Raylib::Vector2::getVector() const {
    return Vector2(_x, _y);
}
