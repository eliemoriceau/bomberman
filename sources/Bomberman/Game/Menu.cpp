#include "Menu.hpp"

Menu *Menu::_instance = nullptr;

Menu *Menu::getInstance() {
    if (_instance == nullptr)
        _instance = new Menu();
    return _instance;
}

Menu::Menu() {
    _mapSize = 7;
    _nbPlayer = 1;
}

ECS::Entity Menu::createBtn(std::vector<std::string> pathStateTexture, const std::string &soundPath, int posX, int posY,
                            void (*callback)()) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto screenWidth = Raylib::Window::getWidth();
    auto screenHeight = Raylib::Window::getHeight();
    auto btn = std::make_shared<Raylib::Button>(pathStateTexture.at(0), pathStateTexture.at(1), pathStateTexture.at(2),
                                                soundPath);
    auto pos = std::make_shared<Raylib::Vector3>(
            (float) screenWidth / 2 - (float) btn->getTextureVector()[0]->getTexture().width / 2 + (float) posX,
            (float) screenHeight / 2 - (float) btn->getTexture().height / 2 + (float) posY, (float) 0.0);
    auto button_1 = ecsHandler->createEntity();

    btn->setButtonPosition(pos->x, pos->y);

    ECS::ClickableComponent clickableComponent = {
            {pos->x, pos->y, (float) btn->getTexture().width, (float) btn->getTexture().height}, callback};
    ECS::Render2dComponent render2DComponent = {ECS::BUTTON, nullptr, nullptr, btn, std::make_shared<bool>(false)};
    ECS::TransformComponent transformComponent = {pos, pos, nullptr};
    ecsHandler->addComponent(button_1, clickableComponent);
    ecsHandler->addComponent(button_1, transformComponent);
    ecsHandler->addComponent(button_1, render2DComponent);

    return (button_1);
}

void loadInitWrapper() {
    Menu::displayMenu(Menu::getInstance()->getSettingsEntities(), false);
    Menu::getInstance()->loadGame(0);
    Game::getInstance()->setState(Game::GAME);
}

void continousInitWrapper() {
    Menu::displayMenu(Menu::getInstance()->getMenuEntities(), false);
    Menu::getInstance()->loadGame(1);
    Game::getInstance()->setState(Game::GAME);

}

void Menu::loadGame(int load) {
    auto game = Game::getInstance();
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    ecsHandler->clear();
    _menuEntitiesPause.clear();
    initiateMenuPause();
    initiateMenuEnd();
    game->setGenerationsValues(_nbPlayer, _mapSize, _mapSize);
    game->spawnAndGenerateMap(load);
}


void setStateStart() {
    auto game = Game::getInstance();
    game->setState(Game::MENU_START);
}

void setStatePause() {
    auto game = Game::getInstance();
    game->setState(Game::MENU_PAUSE);
}

void setStateGame() {
    auto game = Game::getInstance();
    Menu::displayMenu(Menu::getInstance()->getMenuEntitiesPause(), false);
    game->setState(Game::GAME);
}

void quiteGame() {
    auto game = Game::getInstance();
    game->setState(Game::QUIT);
}

void Menu::settingsInitWrapper() {
    Menu::displayMenu(Menu::getInstance()->getMenuEntities(), false);
    Menu::getInstance()->initiateSettings();
    Menu::displayMenu(Menu::getInstance()->getSettingsEntities(), true);
}

void howToPlayInitWrapper() {
    Menu::displayMenu(Menu::getInstance()->getMenuEntities(), false);
    Menu::getInstance()->initiateHowToPlay();
    Menu::displayMenu(Menu::getInstance()->getHowEntities(), true);
}

void Menu::mapUp() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    _mapSize += 2;
    if (_mapSize > 21)
        _mapSize = 21;

    auto text = ecsHandler->getComponent<ECS::Render2dComponent>(_settingsEntities[3]);
    text.text->setText(std::to_string(_mapSize));
}

void Menu::mapDown() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    _mapSize -= 2;
    if (_mapSize < 7)
        _mapSize = 7;

    auto text = ecsHandler->getComponent<ECS::Render2dComponent>(_settingsEntities[3]);
    text.text->setText(std::to_string(_mapSize));
}

void Menu::playerDown() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    _nbPlayer -= 1;
    if (_nbPlayer < 1)
        _nbPlayer = 1;

    auto text = ecsHandler->getComponent<ECS::Render2dComponent>(_settingsEntities[6]);
    text.text->setText(std::to_string(_nbPlayer));
}

void Menu::playerUp() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    _nbPlayer += 1;
    if (_nbPlayer > 4)
        _nbPlayer = 4;

    auto text = ecsHandler->getComponent<ECS::Render2dComponent>(_settingsEntities[6]);
    text.text->setText(std::to_string(_nbPlayer));
}

void mapUpWrapper() {
    Menu::getInstance()->mapUp();
}

void mapDownWrapper() {
    Menu::getInstance()->mapDown();
}

void playerDownWrapper() {
    Menu::getInstance()->playerDown();
}

void playerUpWrapper() {
    Menu::getInstance()->playerUp();
}

void menuWrapper() {
    Menu::displayMenu(Menu::getInstance()->getHowEntities(), false);
    Menu::getInstance()->backToMenu();
    Menu::displayMenu(Menu::getInstance()->getMenuEntities(), true);
}

void Menu::backToMenu() {
    initiateMenu();
}

void Menu::clearHowToPlay() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto entity : _howEntities) {
        ecsHandler->removeEntity(entity);
    }
    _howEntities.clear();
}

void Menu::removeAll() {
    clearMenu();
    clearSettings();
    clearHowToPlay();
    clearPause();
    clearEnd();
}

void Menu::clearAll() {
    _menuEntities.clear();
    _settingsEntities.clear();
    _howEntities.clear();
    _menuEntitiesPause.clear();
    _end.clear();
}

void Menu::clearMenu() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto entity : _menuEntities) {
        ecsHandler->removeEntity(entity);
    }
    _menuEntities.clear();
}

void quitMenu() {
    exit(0);
}

void Menu::clearSettings() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto entity : _settingsEntities) {
        ecsHandler->removeEntity(entity);
    }
    _settingsEntities.clear();
}

void Menu::clearPause() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto entity : _menuEntitiesPause) {
        ecsHandler->removeEntity(entity);
    }
    _menuEntitiesPause.clear();
}

void Menu::initiateHowToPlay() {
    std::vector<std::string> _texturesStart;
    _texturesStart.emplace_back(MENU_MENU_1);
    _texturesStart.emplace_back(MENU_MENU_2);
    _texturesStart.emplace_back(MENU_MENU_3);

    _howEntities.push_back(EntityCreator::createTexture(newVector(0, 0, 0), newVector(1, 1, 1), MENU_HOW_TO_PLAY));
    _howEntities.push_back(createBtn(_texturesStart, MENU_SOUND, 400, -400, &menuWrapper));
}

void Menu::initiateSettings() {
    auto screenWidth = Raylib::Window::getWidth();

    std::vector<std::string> _textures;
    _textures.emplace_back(MENU_UP_1);
    _textures.emplace_back(MENU_UP_2);
    _textures.emplace_back(MENU_UP_3);

    std::vector<std::string> _textures1;
    _textures1.emplace_back(MENU_DOWN_1);
    _textures1.emplace_back(MENU_DOWN_2);
    _textures1.emplace_back(MENU_DOWN_3);

    std::vector<std::string> _texturesStart;
    _texturesStart.emplace_back(MENU_START_3);
    _texturesStart.emplace_back(MENU_START_2);
    _texturesStart.emplace_back(MENU_START_1);

    std::vector<std::string> _texturesBack;
    _texturesBack.emplace_back(MENU_MENU_1);
    _texturesBack.emplace_back(MENU_MENU_2);
    _texturesBack.emplace_back(MENU_MENU_3);

    _settingsEntities.push_back(EntityCreator::createTexture(newVector(0, 0, 0), newVector(1, 1, 1), MENU_BACKGROUND));
    _settingsEntities.push_back(
            EntityCreator::createText(newVector(screenWidth / 2 + 150, 300, 0), newVector(70, 1, 1), "Game Settings"));
    _settingsEntities.push_back(EntityCreator::createText(newVector(screenWidth / 2 + 230, 500, 0), newVector(50, 1, 1),
                                                          "Taille de la map"));
    _settingsEntities.push_back(
            EntityCreator::createText(newVector(screenWidth / 2 + 400, 450, 0), newVector(50, 1, 1), "7"));
    _settingsEntities.push_back(createBtn(_textures, MENU_SOUND, 150, -20, &mapUpWrapper));
    _settingsEntities.push_back(createBtn(_textures1, MENU_SOUND, 700, -20, &mapDownWrapper));
    _settingsEntities.push_back(
            EntityCreator::createText(newVector(screenWidth / 2 + 400, 650, 0), newVector(50, 1, 1), "1"));
    _settingsEntities.push_back(EntityCreator::createText(newVector(screenWidth / 2 + 180, 700, 0), newVector(50, 1, 1),
                                                          "Nombre de joueurs"));
    _settingsEntities.push_back(createBtn(_textures, MENU_SOUND, 120, 180, &playerUpWrapper));
    _settingsEntities.push_back(createBtn(_textures1, MENU_SOUND, 720, 180, &playerDownWrapper));
    _settingsEntities.push_back(createBtn(_texturesStart, MENU_SOUND, 435, 370, &loadInitWrapper));
    _settingsEntities.push_back(createBtn(_texturesBack, MENU_SOUND, -300, -400, &menuWrapper));
}

void Menu::initiateMenu() {

    std::vector<std::string> _texturesStart;
    _texturesStart.emplace_back(MENU_NEW_1);
    _texturesStart.emplace_back(MENU_NEW_2);
    _texturesStart.emplace_back(MENU_NEW_3);
    std::vector<std::string> _texturesQuit;
    _texturesQuit.emplace_back(MENU_QUIT_3);
    _texturesQuit.emplace_back(MENU_QUIT_1);
    _texturesQuit.emplace_back(MENU_QUIT_2);
    std::vector<std::string> _texturesHTP;
    _texturesHTP.emplace_back(MENU_HOW_1);
    _texturesHTP.emplace_back(MENU_HOW_3);
    _texturesHTP.emplace_back(MENU_HOW_2);
    std::vector<std::string> _texturesLoad;
    _texturesLoad.emplace_back(MENU_LOAD_3);
    _texturesLoad.emplace_back(MENU_LOAD_1);
    _texturesLoad.emplace_back(MENU_LOAD_2);

    _menuEntities.push_back(EntityCreator::createTexture(newVector(0, 0, 0), newVector(1, 1, 1), MENU_BACKGROUND));

    _menuEntities.push_back(createBtn(_texturesStart, MENU_SOUND, 400, -200, &settingsInitWrapper));
    _menuEntities.push_back(createBtn(_texturesLoad, MENU_SOUND, 400, 0, &continousInitWrapper));
    _menuEntities.push_back(createBtn(_texturesHTP, MENU_SOUND, 400, 200, &howToPlayInitWrapper));
    _menuEntities.push_back(createBtn(_texturesQuit, MENU_SOUND, 400, 400, &quitMenu));
}

void Menu::startMenu(Raylib::Window *window) {
    window->beginDrawing();
    window->clearBackground();
    _background->drawTexture();
    window->endDrawing();
}

void Menu::initiateMenuPause() {
    std::vector<std::string> _texturesStart;
    _texturesStart.emplace_back(MENU_RESUME_3);
    _texturesStart.emplace_back(MENU_RESUME_1);
    _texturesStart.emplace_back(MENU_RESUME_2);
    std::vector<std::string> _texturesQuit;
    _texturesQuit.emplace_back(MENU_QUIT_3);
    _texturesQuit.emplace_back(MENU_QUIT_1);
    _texturesQuit.emplace_back(MENU_QUIT_2);

    _menuEntitiesPause.push_back(createBtn(_texturesStart, MENU_SOUND, 0, -200, &setStateGame));
    _menuEntitiesPause.push_back(createBtn(_texturesQuit, MENU_SOUND, 0, 200, &quitMenu));
}

const std::vector<ECS::Entity> &Menu::getMenuEntities() const {
    return _menuEntities;
}

const std::vector<ECS::Entity> &Menu::getMenuEntitiesPause() const {
    return _menuEntitiesPause;
}

const std::vector<ECS::Entity> &Menu::getSettingsEntities() const {
    return _settingsEntities;
}

const std::vector<ECS::Entity> &Menu::getHowEntities() const {
    return _howEntities;
}

void Menu::displayMenu(const std::vector<ECS::Entity> &list, bool value) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto entity : list) {
        auto render = ecsHandler->getComponent<ECS::Render2dComponent>(entity);
        *render.enabled = value;
    }
}

void restart()
{
    Game::getInstance()->restartGame();
}

void Menu::initiateMenuEnd()
{
    auto screenWidth = Raylib::Window::getWidth();

    std::vector<std::string> _texturesStart;
    _texturesStart.emplace_back(MENU_NEW_1);
    _texturesStart.emplace_back(MENU_NEW_3);
    _texturesStart.emplace_back(MENU_NEW_2);
    std::vector<std::string> _texturesQuit;
    _texturesQuit.emplace_back(MENU_QUIT_3);
    _texturesQuit.emplace_back(MENU_QUIT_1);
    _texturesQuit.emplace_back(MENU_QUIT_2);


    _winner = EntityCreator::createText(newVector(screenWidth / 2 - 250, 100, 0), newVector(125, 1, 1), "player");
    _end.push_back(_winner);
    _end.push_back(
            EntityCreator::createText(newVector(screenWidth / 2 - 375, 300, 0), newVector(200, 1, 1), "You Win "));
    _end.push_back(createBtn(_texturesStart, MENU_SOUND, 0, 25, &restart));
    _end.push_back(createBtn(_texturesQuit, MENU_SOUND, 0, 250, &quitMenu));
}

void Menu::displayEnd()
{
    auto text = ECS::ECSHandler::getInstance()->getComponent<ECS::Render2dComponent>(_winner);
    std::string player("Player ");
    player.push_back(Game::getIdWinner());
    text.text->setText(player);
    displayMenu(_end, true);
}

const std::vector<ECS::Entity> &Menu::getEnd() const
{
    return _end;
}

void Menu::clearEnd() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    for (auto entity : _end) {
        ecsHandler->removeEntity(entity);
    }
    _end.clear();
}