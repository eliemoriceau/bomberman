//
// Created by marin on 12/06/2021.
//


#pragma once

#include "raylib.h"
#include <string>

namespace Raylib {
    class ColorRGB {
    public:
        ColorRGB(int r, int g, int b, int a);

        ~ColorRGB() = default;

        Color getColor() const;

    private:
        int _r;
        int _g;
        int _b;
        int _a;
    };
}
