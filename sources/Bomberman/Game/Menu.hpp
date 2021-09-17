#pragma once

#include "Game.hpp"
#include "Button.hpp"
#include "ClickableSystem.hpp"
#include "ClickableComponent.hpp"
#include "RenderComponent.hpp"
#include "Render2DSystem.hpp"
#include "Window.hpp"
#include "Vector3.hpp"
#include "EntityCreator.hpp"
#include <vector>

class Menu {
public:
    ~Menu() = default;

    static Menu *getInstance();

    static ECS::Entity
    createBtn(std::vector<std::string> pathStateTexture, const std::string &soundPath, int posX, int posY,
              void (*callback)());

    void startMenu(Raylib::Window *window);

    void initiateMenu();

    void clearMenu();

    void removeAll();

    void clearSettings();

    void initiateSettings();

    void initiateHowToPlay();

    void backToMenu();

    void clearHowToPlay();

    void mapUp();

    void mapDown();

    void playerDown();

    void playerUp();

    void loadGame(int load);

    void initiateMenuPause();

    void clearPause();

    static void displayMenu(const std::vector<ECS::Entity> &list, bool value);

    const std::vector<ECS::Entity> &getMenuEntities() const;

    const std::vector<ECS::Entity> &getMenuEntitiesPause() const;

    const std::vector<ECS::Entity> &getSettingsEntities() const;

    const std::vector<ECS::Entity> &getHowEntities() const;

    void initiateMenuEnd();

    static void settingsInitWrapper();

    void displayEnd();

    const std::vector<ECS::Entity> &getEnd() const;

    void clearEnd();

    void clearAll();

private:
    Menu();

    static Menu *_instance;
    Raylib::Texture *_background{};
    std::vector<ECS::Entity> _menuEntities;
    std::vector<ECS::Entity> _menuEntitiesPause;
    std::vector<ECS::Entity> _end;
    std::vector<ECS::Entity> _settingsEntities;
    std::vector<ECS::Entity> _howEntities;
    ECS::Entity _winner;
    int _mapSize;
    int _nbPlayer;


};