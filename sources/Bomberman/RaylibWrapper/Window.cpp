/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Espace de travail)
** File description:
** Window
*/

#include "Window.hpp"

Raylib::Window *Raylib::Window::_singleton = nullptr;

Raylib::Window::Window(int width, int height, const std::string &title, int fps) : _volume(0.5) {
    init(width, height, title, fps);
}

Raylib::Window &Raylib::Window::beginDrawing() {
    BeginDrawing();
    return *this;
}

Raylib::Window &Raylib::Window::clearBackground() {
    ClearBackground(LIGHTGRAY);
    return *this;
}

void Raylib::Window::init(int width, int height, const std::string &title, int fps) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fps);
    InitAudioDevice();
    SetMasterVolume(0.4);
    SetExitKey(KEY_NULL);
}

Raylib::Window *Raylib::Window::createWindow(int width, int height, const std::string &title, int fps) {
    if (_singleton == nullptr) {
        _singleton = new Window(width, height, title, fps);
        SetConfigFlags(FLAG_MSAA_4X_HINT);
    }
    return _singleton;
}

bool Raylib::Window::isWindowReady() {
    return _singleton != nullptr;
}

Raylib::Window &Raylib::Window::clearState(unsigned int flag) {
    ClearWindowState(flag);
    return *this;
}

void Raylib::Window::close() {
    CloseAudioDevice();
    CloseWindow();
}

Raylib::Window &Raylib::Window::endDrawing() {
    EndDrawing();
    return *this;
}

int Raylib::Window::getFPS() {
    return GetFPS();
}

float Raylib::Window::getFrameTime() {
    return GetFrameTime();
}

void *Raylib::Window::getHandle() {
    return GetWindowHandle();
}

int Raylib::Window::getHeight() {
    return GetScreenHeight();
}

double Raylib::Window::getTime() {
    return GetTime();
}

int Raylib::Window::getWidth() {
    return GetScreenWidth();
}

bool Raylib::Window::isCursorOnScreen() {
    return IsCursorOnScreen();
}

bool Raylib::Window::isFocused() {
    return IsWindowFocused();
}

bool Raylib::Window::isFullscreen() {
    return IsWindowFullscreen();
}

bool Raylib::Window::isHidden() {
    return IsWindowHidden();
}

bool Raylib::Window::isMaximized() {
    return IsWindowMaximized();
}

bool Raylib::Window::isMinimized() {
    return IsWindowMinimized();
}

bool Raylib::Window::isResized() {
    return IsWindowResized();
}

bool Raylib::Window::isState(unsigned int flag) {
    return IsWindowState(flag);
}

Raylib::Window &Raylib::Window::maximize() {
    MaximizeWindow();
    return *this;

}

Raylib::Window &Raylib::Window::minimize() {
    MinimizeWindow();
    return *this;
}

Raylib::Window &Raylib::Window::restore() {
    RestoreWindow();
    return *this;

}

Raylib::Window &Raylib::Window::setMinSize(int width, int height) {
    SetWindowMinSize(width, height);
    return *this;
}

Raylib::Window &Raylib::Window::setMonitor(int monitor) {
    SetWindowMonitor(monitor);
    return *this;
}

Raylib::Window &Raylib::Window::setPosition(int x, int y) {
    SetWindowPosition(x, y);
    return *this;
}

Raylib::Window &Raylib::Window::setSize(int width, int height) {
    SetWindowSize(width, height);
    return *this;
}

Raylib::Window &Raylib::Window::setState(unsigned int flag) {
    SetWindowState(flag);
    return *this;
}

Raylib::Window &Raylib::Window::setTargetFPS(int fps) {
    SetTargetFPS(fps);
    return *this;
}

Raylib::Window &Raylib::Window::setTitle(const std::string &title) {
    SetWindowTitle(title.c_str());
    return *this;
}

bool Raylib::Window::shouldClose() {
    return WindowShouldClose();
}

Raylib::Window &Raylib::Window::toggleFullscreen() {
    ToggleFullscreen();
    return *this;
}

bool Raylib::Window::isInScreenX(const Vector2 &position, const Vector2 &size) {
    return !((position.getX() >= ((float) GetScreenWidth() - size.getX())) || (position.getX() <= size.getY()));
}

bool Raylib::Window::isInScreenY(const Vector2 &position, const Vector2 &size) {
    return !((position.getY() >= ((float) GetScreenHeight() - size.getX())) || (position.getY() <= size.getY()));
}

bool Raylib::Window::isInScreen(const Vector2 &position, const Vector2 &size) {
    return isInScreenX(position, size) && isInScreenY(position, size);
}

Raylib::Window::~Window() {
    close();
}

void Raylib::Window::setVolumeMaster(float volume) {
    SetMasterVolume(volume);
}

void Raylib::Window::setVolume(float volume) {
    _volume = volume;
    setVolumeMaster(_volume);
}
