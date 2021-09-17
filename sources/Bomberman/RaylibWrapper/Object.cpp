/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo
** File description:
** Object
*/

#include "Object.hpp"

Raylib::Object::Object(std::string filename, float scale) : _filename(std::move(filename)), _scale(scale),
                                                            _image(LoadImage(_filename.c_str())),
                                                            _texture(LoadTextureFromImage(_image)) {
}

void Raylib::Object::generateCubeMesh(::Vector3 cubeSize) {
    _mesh = ::GenMeshCubicmap(_image, cubeSize);
    _model = ::LoadModelFromMesh(_mesh);
}

void Raylib::Object::loadObjectTexture(const std::string &filename) {
    _objectTexture = LoadTexture(filename.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _objectTexture;
}

::Texture2D Raylib::Object::getTexture() {
    return _texture;
}

::Image Raylib::Object::getImage() {
    return _image;
}

::Model Raylib::Object::getModel() {
    return _model;
}

float Raylib::Object::getScale() const {
    return _scale;
}

void Raylib::Object::setScale(float scale) {
    _scale = scale;
}
