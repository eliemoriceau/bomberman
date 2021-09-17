//
// Created by marin on 12/06/2021.
//

#include "Color.hpp"

Raylib::ColorRGB::ColorRGB(int r, int g, int b, int a) : _r(r), _g(g), _b(b), _a(a) {

}

Color Raylib::ColorRGB::getColor() const {
    return {(unsigned char) _r, (unsigned char) _g, (unsigned char) _b, (unsigned char) _a};
}