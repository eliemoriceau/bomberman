/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Input
*/

#include "Input.hpp"

/////////////KEYBOARD_INPUT/////////////////
bool Raylib::Input::isKeyMaintain(int key) {
    return (IsKeyDown(key));
}

bool Raylib::Input::isKeyPressed(int key) {
    return (IsKeyPressed(key));
}

bool Raylib::Input::isKeyReleased(int key) {
    return (IsKeyReleased(key));
}

/////////////MOUSE_BUTTON/////////////////
bool Raylib::Input::isMouseButtonReleased(int button) {
    return (IsMouseButtonReleased(button));
}

bool Raylib::Input::isMouseButtonPressed(int button) {
    return (IsMouseButtonPressed(button));
}

bool Raylib::Input::isMouseButtonMaintain(int button) {
    return (IsMouseButtonDown(button));
}

/////////////MOUSE_POSITION/////////////////
int Raylib::Input::getMousePosX() {
    return (GetMouseX());
}

int Raylib::Input::getMousePosY() {
    return (GetMouseY());
}

Vector2 Raylib::Input::getMousePositionXY() {
    return (GetMousePosition());
}

bool Raylib::Input::checkCollisionPointRec(Vector2 point, Rectangle rec) {
    return (CheckCollisionPointRec(point, rec));
}