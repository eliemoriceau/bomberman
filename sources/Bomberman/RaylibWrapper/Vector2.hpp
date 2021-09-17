/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "raylib.h"
#include <ostream>

namespace Raylib {
    class Vector2 {
    public:
        Vector2(float x, float y);

        Vector2(const Vector2 &);

        ~Vector2() = default;

        void add(const Raylib::Vector2 &add);

        float getX() const;

        float getY() const;

        void setX(float value);

        void setY(float value);

        void set(float x, float y);

        Vector2 getVector() const;

        float _x;
        float _y;
    };
}
