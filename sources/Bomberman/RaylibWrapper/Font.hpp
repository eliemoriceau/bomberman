/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "raylib.h"
#include <string>

namespace Raylib {
    class Font {
    public:
        explicit Font(std::string fontPath);

        virtual ~Font();

        const std::string &getFontPath() const;

        void setFontPath(const std::string &fontPath);

        ::Font &getFont();

        void setFont(const ::Font &font);

    private:
        std::string _fontPath;
        ::Font _font;
    };
}