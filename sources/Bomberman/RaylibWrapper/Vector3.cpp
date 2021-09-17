/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "Vector3.hpp"

Raylib::Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Raylib::Vector3::getX() const {
    return x;
}

void Raylib::Vector3::setX(float new_x) {
    Vector3::x = new_x;
}

float Raylib::Vector3::getY() const {
    return y;
}

void Raylib::Vector3::setY(float new_y) {
    Vector3::y = new_y;
}

float Raylib::Vector3::getZ() const {
    return z;
}

void Raylib::Vector3::setZ(float new_z) {
    Vector3::z = new_z;
}

::Vector3 Raylib::Vector3::getVector() {
    return {x, y, z};
}

Raylib::Vector3 Raylib::Vector3::add(const Raylib::Vector3 &add) {

    return Raylib::Vector3(x += add.x, y += add.y, z += add.z);
}

bool Raylib::Vector3::operator==(const Raylib::Vector3 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z;
}

bool Raylib::Vector3::operator!=(const Raylib::Vector3 &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Vector3 &vector3) {
    os << "x: " << vector3.x << " y: " << vector3.y << " z: " << vector3.z;
    return os;
}