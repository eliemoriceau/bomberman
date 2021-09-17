/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Texture
*/

#pragma once

#include <raylib.h>
#include <string>

namespace Raylib {
    class Texture {
    public:
        Texture(std::string filename, int posX, int posY, Color tint);

        ~Texture();

        int getPosX() const;

        void setPosX(int posX);

        int getPosY() const;

        void setPosY(int posY);

        void setColor(::Color tint);

        ::Color getColor();

        void loadTexture();

        void drawTexture();

        const ::Texture2D &getTexture() const;

    private:
        std::string _filename;
        ::Texture2D _texture{};
        int _posX;
        int _posY;
        ::Color _tint;
    };
}