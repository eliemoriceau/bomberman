/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Model
*/

#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "raylib.h"
#include "raymath.h"
#include "Vector3.hpp"
#include "Texture.hpp"

namespace Raylib {
    class Model {
    public:
        Model(const std::string &modelFile, const std::shared_ptr<Raylib::Texture> &texture,
              const std::string &animFile, const std::shared_ptr<Raylib::Vector3> &scale);

        ~Model();

        ::Vector3 getPosition();

        void setPosition(::Vector3 position);

        float getPositionX() const;

        void setPositionX(float x);

        float getPositionY() const;

        void setPositionY(float z);

        float getPositionZ() const;

        void setPositionZ(float z);

        void animModel();

        void drawModel();

        void UnAnimModel();

        void setRotation(::Vector3 rot);

        const Vector3 &getScale() const;

        void setScale(const Vector3 &scale);

        const Texture2D &getTexture() const;

        void setTexture(const Texture2D &texture);

    private:
        ::Model _model{};
        ::Texture2D _texture{};
        ::ModelAnimation *_anim;
        int _animCount;
        int _animFrame;
        ::Vector3 _position{};
        ::Vector3 _rotation_axes{};
        Raylib::Vector3 _scale;
    };
}
