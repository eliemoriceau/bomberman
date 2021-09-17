/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Music
*/

#include "Input.hpp"
#include "Music.hpp"
#include <utility>

Raylib::Music::Music(std::string filename) : _filename(std::move(filename)), _music(LoadMusicStream(_filename.c_str())),
                                             _pause(false) {
}

Raylib::Music::~Music() {
    UnloadMusicStream(_music);
}

void Raylib::Music::playMusic() {
    PlayMusicStream(_music);
}

void Raylib::Music::pauseMusic() {
    if (Raylib::Input::isKeyReleased(KEY_L)) {
        _pause = !_pause;
        if (_pause) {
            PauseMusicStream(_music);
        } else {
            ResumeMusicStream(_music);
        }
    }
}

void Raylib::Music::update() {
    UpdateMusicStream(_music);
}

void Raylib::Music::resumeMusic() {
    ResumeMusicStream(_music);
}

void Raylib::Music::setVolumeMusic(float volume) {
    SetMusicVolume(_music, volume);
}

