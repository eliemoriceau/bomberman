/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-marius1.glo [WSL: Ubuntu]
** File description:
** Sound
*/

#include "Sound.hpp"

Raylib::Sound::Sound(std::string filename) : _filename(std::move(filename)), _sound(LoadSound(_filename.c_str())) {
}

Raylib::Sound::~Sound() {
    ::UnloadSound(_sound);
}

void Raylib::Sound::playSound() {
    PlaySound(_sound);
}

void Raylib::Sound::stopSound() {
    StopSound(_sound);
}

void Raylib::Sound::pauseSound() {
    PauseSound(_sound);
}

void Raylib::Sound::resumeSound() {
    ResumeSound(_sound);
}


const ::Sound &Raylib::Sound::getSound() const {
    return _sound;
}

void Raylib::Sound::playedSoundIf() {
    if (!IsSoundPlaying(_sound))
        playSound();
}
