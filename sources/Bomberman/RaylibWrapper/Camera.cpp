/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Camera
*/

#include "Camera.hpp"
#include "Vector3.hpp"

Raylib::Camera::Camera(Vector3 position, Vector3 target, Vector3 up, float fovY, int projection)
        : _position(position),
          _target(target),
          _up(up), _fovY(fovY),
          _projection(projection) {
    _camera = {{_position.x, _position.y, _position.z}, {target.x, target.y, target.z}, {_up.x, _up.y, _up.z}, _fovY,
               _projection};
}

void Raylib::Camera::beginMode3D() {
    BeginMode3D(_camera);
}

void Raylib::Camera::endMode3D() {
    EndMode3D();
}

void Raylib::Camera::setCameraMode(int mode) {
    SetCameraMode(_camera, mode);
}

void Raylib::Camera::updateCamera() {
    UpdateCamera(&_camera);
}

void Raylib::Camera::setTarget(const std::shared_ptr<Raylib::Vector3> &target) {
    _camera.target = {target->x, target->y, target->z};
}

const Raylib::Vector3 &Raylib::Camera::getPosition() const {
    return _position;
}

void Raylib::Camera::setPosition(const Raylib::Vector3 &position) {
    _position = position;
    _camera.position = _position.getVector();
}
