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
    class Vector3 {
    public:
        Vector3(float x, float y, float z);

        ~Vector3() = default;

        float getX() const;

        bool operator==(const Vector3 &rhs) const;

        bool operator!=(const Vector3 &rhs) const;

        void setX(float new_x);

        float getY() const;

        void setY(float new_y);

        float getZ() const;

        void setZ(float new_z);

        ::Vector3 getVector();

        Vector3 add(const Vector3 &add);


        float x;
        float y;
        float z;
    };

    std::ostream &operator<<(std::ostream &os, const Vector3 &vector3);
}