/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Input
*/

#pragma once

#include "raylib.h"

namespace Raylib {
    enum Keys {
        LEFT, UP, RIGHT, DOWN, ESC,
        NONE
    };

    class Input {
    public:
        Input() = default;

        ~Input() = default;

        /*KEYBOARD_INPUT*/
        static bool isKeyMaintain(int key);

        static bool isKeyPressed(int key);

        static bool isKeyReleased(int key);

        /*MOUSE_BUTTON*/
        static bool isMouseButtonReleased(int button);

        static bool isMouseButtonPressed(int button);

        static bool isMouseButtonMaintain(int button);

        /*MOUSE_POSITION*/
        static int getMousePosX();

        static int getMousePosY();

        static Vector2 getMousePositionXY();

        static bool checkCollisionPointRec(::Vector2 point, Rectangle rec);
    };
}