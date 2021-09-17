//
// Created by marin on 11/06/2021.
//

#include "Game.hpp"
#include "Music.hpp"
#include "PickableSystem.hpp"
#include "VectorUtils.hpp"
#include "RemovableSystem.hpp"
#include "AssetManager.hpp"
#include "raymath.h"
#include "AISystem.hpp"

Game *Game::_instance = nullptr;

Game::Game() {
    _state = MENU_START;
    restart = false;
}

void Game::setState(Game::SCENE defineState) {
    _state = defineState;
}

Game::SCENE Game::getState() {
    return (_state);
}

void Game::restartGame() {
    remove(SAVE_FILE);
    if (restart)
        return;
    restart = true;
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    MapManager *map_manager = MapManager::getInstance();
    PlayerManager *player_manager = PlayerManager::getInstance();

    player_manager->clearAll();
    map_manager->clearAll();
    ecsHandler->clear();
    HUD::getInstance()->clearHud();
    Menu::getInstance()->clearAll();
    Menu::getInstance()->initiateMenu();
    Menu::displayMenu(Menu::getInstance()->getMenuEntities(), true);

    Game::setState(MENU_START);
}

void Game::setGenerationsValues(int nb_player, int width, int height) {
    _playerCount = nb_player;
    _width = width;
    _height = height;
}

void Game::spawnAndGenerateMap(int load) {
    restart = false;
    MapManager::getInstance()->generateMap(_width, _height, _playerCount, load);
    PlayerManager::getInstance()->createAllPlayers(_playerCount);
}

void Game::start(int nb_player, int width, int height) {
    _width = width;
    _height = height;
    _playerCount = nb_player;

    auto *ecsHandler = ECS::ECSHandler::getInstance();
    Raylib::Window *window = Raylib::Window::createWindow(1920, 1080, "Bomberman", 60);
    auto *camera = new Raylib::Camera({.0f, 50.0f, 4.0f}, {0.0f, -10.0f, 0.0f}, {0.0f, 17.0f, 0.0f}, 25.0f, 0);

    RegisterManager::registerComponents();

    auto renderSystem = ecsHandler->registerSystem<ECS::RenderSystem>();
    auto colliderSystem = ecsHandler->registerSystem<ECS::ColliderSystem>();
    auto moveSystem = ecsHandler->registerSystem<ECS::MoveSystem>();
    auto controllableSystem = ecsHandler->registerSystem<ECS::ControllableSystem>();
    auto bombSystem = ecsHandler->registerSystem<ECS::BombSystem>();
    auto _health_system = ecsHandler->registerSystem<ECS::HealthSystem>();
    auto bonusSystem = ecsHandler->registerSystem<ECS::BonusSystem>();
    auto pickableSystem = ecsHandler->registerSystem<ECS::PickableSystem>();
    auto removableSystem = ecsHandler->registerSystem<ECS::RemovableSystem>();
    auto render2Dsystem = ecsHandler->registerSystem<ECS::Render2dSystem>();
    auto clikable = ecsHandler->registerSystem<ECS::ClickableSystem>();
    auto ai = ecsHandler->registerSystem<ECS::AISystem>();
    RegisterManager::registerUids();

    Raylib::Music music("Resources/music.mp3");
    music.playMusic();
    Menu::getInstance()->initiateMenu();
//    Menu::getInstance()->initiateMenuPause();
//    Menu::getInstance()->initiateMenuEnd();
    music.setVolumeMusic(0.15);
    Menu::displayMenu(Menu::getInstance()->getMenuEntities(), true);

    while (!Raylib::Window::shouldClose()) {
        if (Raylib::Input::isKeyReleased(KEY_ESCAPE)) {
            if (Game::getState() == MENU_PAUSE) {
                Menu::displayMenu(Menu::getInstance()->getMenuEntitiesPause(), false);
                Game::setState(GAME);
            } else if (Game::getState() == GAME) {
                Menu::displayMenu(Menu::getInstance()->getMenuEntitiesPause(), true);
                Game::setState(MENU_PAUSE);
            }
        }
        music.update();
        music.pauseMusic();
        window->beginDrawing();
        camera->beginMode3D();
        window->clearBackground();
        renderSystem->update();
        HUD::getInstance()->updateHudAllPlayer();
        if (Game::getState() == GAME) {
            if (!PlayerManager::getInstance()->getPlayers().empty()) {
                Game::computeCameraTarget(camera);
            }
            removableSystem->update();
            bombSystem->update(bonusSystem);
            _health_system->update();
            moveSystem->update();
            pickableSystem->update();
            ai->update();
            controllableSystem->update();
            colliderSystem->update();
        } else {
            clikable->update();
        }
        Raylib::Camera::endMode3D();
        render2Dsystem->update();
        if (PlayerManager::getInstance()->checkEndingGame()) {
            Game::setState(MENU_PAUSE);
            Menu::getInstance()->displayEnd();
        }
        DrawFPS(102, 120);
        window->endDrawing();
    }
    MapManager::getInstance()->saveMap2DtoFile(SAVE_FILE);
    delete camera;
    delete window;
}

Game *Game::getInstance() {
    if (_instance == nullptr)
        _instance = new Game();
    return _instance;
}

std::shared_ptr<Raylib::Vector3> Game::computeCameraTarget(Raylib::Camera *camera) {
    std::list<ECS::Entity> players = PlayerManager::getInstance()->getPlayers();
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto target = std::make_shared<Raylib::Vector3>((float) 0.0, (float) 0.0, (float) 0.0);
    float maxDistance = -1;

    ECS::Entity old = -1;
    for (auto player : players) {
        if (!PlayerManager::getInstance()->isPlayerDead(player)) {
            auto transform = ecsHandler->getComponent<ECS::TransformComponent>(player);
            if (old != -1) {
                auto transformOld = ecsHandler->getComponent<ECS::TransformComponent>(old);
                float distance = sqrt(pow(transform.position->x - transformOld.position->x, 2) +
                                      pow(transform.position->y - transformOld.position->y, 2) +
                                      pow(transform.position->z - transformOld.position->z, 2));
                if (maxDistance < distance)
                    maxDistance = distance;
            }
            old = player;
            target->x += transform.position->x;
            target->y += transform.position->y;
            target->z += transform.position->z;
        }
    }
    target->x /= (float) players.size();
    target->y /= (float) players.size();
    target->z /= (float) players.size();

    camera->setTarget(target);

    camera->setPosition(
            Raylib::Vector3(target->x, (MapManager::getInstance()->getWidth() * 2) + 10 + maxDistance, target->z + 4));

    return target;
}

char Game::getIdWinner()
{
    auto players = PlayerManager::getInstance()->getPlayers();

    for (auto player : players) {
        if (!PlayerManager::getInstance()->isPlayerDead(player)) {
            auto id = ECS::ECSHandler::getInstance()->getComponent<ECS::TransformComponent>(player).id;
            return id;
        }
    }
    return '\0';
}