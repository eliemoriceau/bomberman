//
// Created by marin on 11/06/2021.
//

#pragma once

#include <cmath>
#include <random>
#include <algorithm>
#include <vector>
#include "Camera.hpp"
#include "Window.hpp"
#include "System.hpp"
#include "ECSHandler.hpp"
#include "raylib.h"
#include "RegisterManager.hpp"
#include "MapManager.hpp"
#include "PlayerManager.hpp"
#include "Menu.hpp"
#include "HUD.hpp"

class Game {
public:
    ~Game() = default;

    enum SCENE {
        MENU_START,
        MENU_PAUSE,
        MENU_SELECTION,
        GAME,
        QUIT
    };

    static Game *getInstance();

    void setState(Game::SCENE defineState);

    SCENE getState();

    void spawnAndGenerateMap(int load);

    void setGenerationsValues(int nb_player, int width, int height);

    void start(int nb_player, int width, int height);

    void restartGame();

    static std::shared_ptr<Raylib::Vector3> computeCameraTarget(Raylib::Camera *camera);

    static char getIdWinner();


private:
    Game();

    static Game *_instance;
    bool restart;
    int _width{};
    int _height{};
    int _playerCount{};
    SCENE _state;
};