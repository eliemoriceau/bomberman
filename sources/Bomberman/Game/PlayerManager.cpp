//
// Created by marin on 14/06/2021.
//

#include "PlayerManager.hpp"
#include "AssetManager.hpp"

PlayerManager *PlayerManager::_instance = nullptr;

bool PlayerManager::checkEndingGame() {
    if (_deadPlayers.size() >= _players.size() - 1)
        return true;
    return false;
}

void PlayerManager::addPlayerToRemoveList(ECS::Entity entity) {
    _deadPlayers.push_back(entity);
}

PlayerManager *PlayerManager::getInstance() {
    if (_instance == nullptr)
        _instance = new PlayerManager();
    return _instance;
}

void PlayerManager::clearAll() {
    _players.clear();
    _deadPlayers.clear();
}

int PlayerManager::getIndexByID(char id) {
    switch (id) {
        case '1':
            return 0;
        case '2':
            return 1;
        case '3':
            return 2;
        case '4':
            return 3;
        default:
            return -1;
    }
}

void PlayerManager::createAllPlayers(int nb_player) {
    const std::vector<std::vector<KeyboardKey>> &inputs = {
            {KEY_W,  KEY_S,    KEY_A,    KEY_D,     KEY_SPACE, KEY_E},
            {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ENTER, KEY_E},
            {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_M,     KEY_E},
            {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_M,     KEY_E}
    };

    const std::vector<std::string> &models = {
            GUY_MODEL_1,
            GUY_MODEL_2,
            GUY_MODEL_3,
            GUY_MODEL_4
    };
    std::map<std::shared_ptr<Raylib::Vector3>, std::tuple<int, int, char>> points = MapManager::getInstance()->getSpawnPoints();
    auto it = points.begin();

    while (it != points.end()) {
        int index = getIndexByID(std::get<2>(it->second));

        if (index >= nb_player) {
            _players.push_back(EntityCreator::createAi(it->first, newVector(0.5f, 1.0f, 0.5f), 0.04f, models[index],{std::get<0>(it->second), std::get<1>(it->second)},std::get<2>(it->second)));
        } else {
            _players.push_back(EntityCreator::createPlayer(it->first, newVector(0.5f, 1.0f, 0.5f), inputs[index], 0.04f,
                                                           models[index],
                                                           {std::get<0>(it->second), std::get<1>(it->second)},
                                                           std::get<2>(it->second)));
        }
        it++;
    }

    HUD::getInstance()->createHUD();
}

ECS::Entity PlayerManager::getPlayerById(int id) {
    auto it = _players.begin();
    for (int i = 0; i < id; i++) {
        ++it;
    }
    return *it;
}

std::list<ECS::Entity> PlayerManager::getPlayers() {
    return _players;
}

std::list<ECS::Entity> PlayerManager::getDeadPlayers() {
    return _deadPlayers;
}

bool PlayerManager::isPlayerDead(ECS::Entity player) {
    return std::find(_deadPlayers.begin(), _deadPlayers.end(), player) != _deadPlayers.end();
}
