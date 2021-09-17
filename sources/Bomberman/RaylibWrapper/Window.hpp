/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Espace de travail)
** File description:
** Window
*/

#pragma once

#include <string>
#include <memory>
#include "Vector2.hpp"

namespace Raylib {
    class Window {
    public:
        Window(Window &) = delete;

        ~Window();

        Window &operator=(Window &) = delete;

        Window &beginDrawing();

        //Window &clearBackground(const ::Color &color=BLACK);
        Window &clearBackground();

        Window &clearState(unsigned int flag);

        static void close();

        static Window *createWindow(int width, int height, const std::string &title, int fps);

        static bool isWindowReady();

        Window &endDrawing();

        static int getFPS();

        static float getFrameTime();

        static void *getHandle();

        static int getHeight();

        //Vector2 getPosition() const;
        //Vector2 getScaleDPI() const;
        //Vector2 getSize();
        static double getTime();

        static int getWidth();

        static void init(int width = 800, int height = 450, const std::string &title = "title", int fps = 60);

        static bool isCursorOnScreen();

        static bool isFocused();

        static bool isFullscreen();

        static bool isHidden();

        static bool isMaximized();

        static bool isMinimized();

        static bool isResized();

        static bool isState(unsigned int flag);

        Window &maximize();

        Window &minimize();

        Window &restore();

        //Window &setIcon(const ::Image &image);
        Window &setMinSize(int width, int height);

        Window &setMonitor(int monitor);

        Window &setPosition(int x, int y);

        //Window &setPosition(const ::Vector2 &position);
        //Window &setSize(const ::Vector2 &position);
        Window &setSize(int width, int height);

        Window &setState(unsigned int flag);

        Window &setTargetFPS(int fps);

        Window &setTitle(const std::string &title);

        static bool shouldClose();

        Window &toggleFullscreen();

        static bool isInScreen(const Vector2 &position, const Vector2 &size = Vector2(0, 0));

        static bool isInScreenX(const Vector2 &position, const Vector2 &size = Vector2(0, 0));

        static bool isInScreenY(const Vector2 &position, const Vector2 &size = Vector2(0, 0));

        static void setVolumeMaster(float volume);

    private:
        explicit Window(int width = 800, int height = 450, const std::string &title = "title", int fps = 60);

    protected:
        static Window *_singleton;
        float _volume;
    public:
        void setVolume(float volume);

    };
}