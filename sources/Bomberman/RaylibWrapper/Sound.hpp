/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Sound
*/

#pragma once

#include "raylib.h"
#include <string>

namespace Raylib {
    class Sound {
    public:
        explicit Sound(std::string filename);

        ~Sound();

        void playSound();

        void stopSound();

        void pauseSound();

        void resumeSound();

        const ::Sound &getSound() const;

        void playedSoundIf();

    private:
        std::string _filename;
        ::Sound _sound;
    };
}