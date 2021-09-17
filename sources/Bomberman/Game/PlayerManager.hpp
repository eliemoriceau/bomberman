//
// Created by marin on 14/06/2021.
//

#pragma once

#include <list>
#include "Entity.hpp"
#include "Vector3.hpp"
#include "Input.hpp"
#include "raylib.h"
#include <vector>
#include "VectorUtils.hpp"
#include "EntityCreator.hpp"
#include <algorithm>
#include <tuple>
#include "HUD.hpp"

class PlayerManager {
public:
    ~PlayerManager() = default;

    static PlayerManager *getInstance();

    void createAllPlayers(int nb_player);

    void addPlayerToRemoveList(ECS::Entity entity);

    static int getIndexByID(char id);

    void clearAll();

    bool checkEndingGame();

    std::list<ECS::Entity> getPlayers();

    std::list<ECS::Entity> getDeadPlayers();

    ECS::Entity getPlayerById(int id);

    bool isPlayerDead(ECS::Entity);

private:
    PlayerManager() = default;

    std::list<ECS::Entity> _players;
    std::list<ECS::Entity> _deadPlayers;

    static PlayerManager *_instance;

};