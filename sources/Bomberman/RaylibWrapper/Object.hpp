/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo
** File description:
** Object
*/

#pragma once

#include <string>
#include "raylib.h"

namespace Raylib {
    class Object {
    public:
        Object(std::string filename, float scale);

        ~Object() = default;

        void generateCubeMesh(::Vector3 CubeSize);

        void loadObjectTexture(const std::string &filename);

        Texture2D getTexture();

        Image getImage();

        Model getModel();

        static void unloadModel(Model model) { (void) model; };

    private:
        std::string _filename;
        Image _image;
        Texture2D _texture;
        Texture2D _objectTexture{};
        Mesh _mesh{};
        Model _model{};
        float _scale;
    public:
        float getScale() const;

        void setScale(float scale);
    };
}
