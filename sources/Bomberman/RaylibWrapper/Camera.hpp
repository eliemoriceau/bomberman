/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Camera
*/

#pragma once

#include <memory>
#include "Vector3.hpp"
#include "raylib.h"

namespace Raylib {
    class Camera {
    public:
        Camera(Vector3 position, Vector3 target, Vector3 up, float fovY, int projection);

        ~Camera() = default;

        void beginMode3D();

        static void endMode3D();

        void setCameraMode(int mode);

        void setTarget(const std::shared_ptr<Raylib::Vector3> &);

        void updateCamera();

    protected:
    private:
        ::Camera _camera{};
        Vector3 _position;
    public:
        const Vector3 &getPosition() const;

        void setPosition(const Vector3 &position);

    private:
        Vector3 _target;
        Vector3 _up;
        float _fovY;
        int _projection;
    };
}