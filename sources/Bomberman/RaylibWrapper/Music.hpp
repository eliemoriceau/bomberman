/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Music
*/

#pragma once

#include "raylib.h"
#include <string>

namespace Raylib {
    class Music {
    public:
        explicit Music(std::string filename);

        ~Music();

        void playMusic();

        void stopMusic() {};

        void pauseMusic();

        void resumeMusic();

        void update();

        void setVolumeMusic(float volume);

    private:
        std::string _filename;
        ::Music _music;
        bool _pause;
    };
}