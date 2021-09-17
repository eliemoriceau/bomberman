/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Model
*/

#include "Model.hpp"
#include "VectorUtils.hpp"

Raylib::Model::Model(const std::string &modelFile, const std::shared_ptr<Raylib::Texture> &texture,
                     const std::string &animFile, const std::shared_ptr<Raylib::Vector3> &scale) :
        _scale(scale->x, scale->y, scale->z) {
    _model = LoadModel(modelFile.c_str());
    _texture = texture->getTexture();
    SetMaterialTexture(&_model.materials[0], MAP_DIFFUSE, _texture);
    if (!animFile.empty())
        _anim = LoadModelAnimations(animFile.c_str(), &_animCount);
    _rotation_axes = {1.0f, 0.0f, 0.0f};
    _animCount = 0;
    _animFrame = 0;
}

Raylib::Model::~Model() {
    UnloadTexture(_texture);
    for (int i = 0; i < _animCount; i++)
        UnloadModelAnimation(_anim[i]);
    UnloadModel(_model);
}

::Vector3 Raylib::Model::getPosition() {
    return _position;
}

void Raylib::Model::setPosition(::Vector3 position) {
    _position = position;
}

float Raylib::Model::getPositionX() const {
    return _position.x;
}

void Raylib::Model::setPositionX(float x) {
    _position.x = x;
}

float Raylib::Model::getPositionY() const {
    return _position.y;
}

void Raylib::Model::setPositionY(float y) {
    _position.y = y;
}

float Raylib::Model::getPositionZ() const {
    return _position.z;
}

void Raylib::Model::setPositionZ(float z) {
    _position.z = z;
}

void Raylib::Model::animModel() {
    _animFrame += 3;
    UpdateModelAnimation(_model, _anim[0], _animFrame);
    if (_animFrame >= _anim[0].frameCount)
        _animFrame = 0;
}

void Raylib::Model::UnAnimModel() {
    _animFrame = 5;
    UpdateModelAnimation(_model, _anim[0], _animFrame);
}

void Raylib::Model::setRotation(::Vector3 rot) {
    _rotation_axes = rot;
}

void Raylib::Model::drawModel() {
    _model.transform = MatrixRotateXYZ(
            {DEG2RAD * _rotation_axes.x, DEG2RAD * _rotation_axes.y, DEG2RAD * _rotation_axes.z});
    DrawModelEx(_model, _position, {1.0f, 0.0f, 0.0f}, -90.0f, _scale.getVector(), WHITE);
}

const Raylib::Vector3 &Raylib::Model::getScale() const {
    return _scale;
}

void Raylib::Model::setScale(const Vector3 &scale) {
    _scale = scale;
}

const Texture2D &Raylib::Model::getTexture() const {
    return _texture;
}

void Raylib::Model::setTexture(const Texture2D &texture) {
    _texture = texture;
}
