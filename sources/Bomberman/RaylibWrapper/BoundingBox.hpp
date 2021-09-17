/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "raylib.h"

namespace Raylib {
    class BoundingBox {
    public:
        BoundingBox(::Vector3 pos, ::Vector3 size);

        ~BoundingBox() = default;

        ::BoundingBox getBox() const;

    private:
        ::Vector3 _pos;
        ::Vector3 _size;
        ::Vector3 _min;
        ::Vector3 _max;
        ::BoundingBox _box;
    };
}
