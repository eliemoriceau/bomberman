/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "AssetManager.hpp"
#include "DefineResources.hpp"
#include "VectorUtils.hpp"

AssetManager *AssetManager::_instance = nullptr;

void AssetManager::addModel(const std::string &name, const std::shared_ptr<Raylib::Model> &newModel) {
    _modelAsset.emplace(name, newModel);
}

std::shared_ptr<Raylib::Model> AssetManager::getModel(const std::string &name) {
    return _modelAsset.at(name);
}

void AssetManager::addColor(const std::string &name, const std::shared_ptr<Raylib::ColorRGB> &newColor) {
    _colorAsset.emplace(name, newColor);
}

std::shared_ptr<Raylib::ColorRGB> AssetManager::getColor(const std::string &name) {
    return _colorAsset.at(name);
}

void AssetManager::addSound(const std::string &name, const std::shared_ptr<Raylib::Sound> &newSound) {
    _soundAsset.emplace(name, newSound);
}

std::shared_ptr<Raylib::Sound> AssetManager::getSound(const std::string &name) {
    return _soundAsset.at(name);
}

void AssetManager::addTexture(const std::string &name, const std::shared_ptr<Raylib::Texture> &newTexture) {
    _textureAsset.emplace(name, newTexture);
}

std::shared_ptr<Raylib::Texture> AssetManager::getTexture(const std::string &name) {
    return _textureAsset.at(name);
}

void AssetManager::addText(const std::string &name, const std::shared_ptr<Raylib::Text> &newText) {
    _textAsset.emplace(name, newText);
}

std::shared_ptr<Raylib::Text> AssetManager::getText(const std::string &name) {
    return _textAsset.at(name);
}

void AssetManager::addButton(const std::string &name, const std::shared_ptr<Raylib::Button> &newButton) {
    _buttonAsset.emplace(name, newButton);
}

std::shared_ptr<Raylib::Button> AssetManager::getButton(const std::string &name) {
    return _buttonAsset.at(name);
}

void AssetManager::addFont(const std::string &name, const std::shared_ptr<Raylib::Font> &newFont) {
    _fontAsset.emplace(name, newFont);
}

std::shared_ptr<Raylib::Font> AssetManager::getFont(const std::string &name) {
    return _fontAsset.at(name);
}

void AssetManager::loadingAsset() {

    std::cout << "loading assets" << std::endl;
//    _modelAsset.emplace(GUY_MODEL, player) ;
    loadTexture();
    loadColor();
    loadAudio();
    loadFonts();
    loadModels();
    std::cout << "finish assets" << std::endl;

}

void AssetManager::loadModels() {
    _modelAsset.emplace(BOMB_MODEL, std::make_shared<Raylib::Model>(BOMB_MODEL, _textureAsset.at(BOMB_TEXTURE), "",
                                                                    std::make_unique<Raylib::Vector3>(1.0f, 1.0f,
                                                                                                      1.0f)));
    _modelAsset.emplace(GUY_MODEL_1,
                        std::make_shared<Raylib::Model>(GUY_MODEL_1, _textureAsset.at(GUY_TEXTURE_1), GUY_ANIMATION_1,
                                                        std::make_unique<Raylib::Vector3>(1.0f, 1.0f, 1.0f)));
    _modelAsset.emplace(GUY_MODEL_2,
                        std::make_shared<Raylib::Model>(GUY_MODEL_2, _textureAsset.at(GUY_TEXTURE_2), GUY_ANIMATION_2,
                                                        std::make_unique<Raylib::Vector3>(1.0f, 1.0f, 1.0f)));
    _modelAsset.emplace(GUY_MODEL_3,
                        std::make_shared<Raylib::Model>(GUY_MODEL_3, _textureAsset.at(GUY_TEXTURE_3), GUY_ANIMATION_3,
                                                        std::make_unique<Raylib::Vector3>(1.0f, 1.0f, 1.0f)));
    _modelAsset.emplace(GUY_MODEL_4,
                        std::make_shared<Raylib::Model>(GUY_MODEL_4, _textureAsset.at(GUY_TEXTURE_4), GUY_ANIMATION_4,
                                                        std::make_unique<Raylib::Vector3>(1.0f, 1.0f, 1.0f)));
}

void AssetManager::loadFonts() {
    _fontAsset.emplace(BASIC_FONT, std::make_shared<Raylib::Font>(BASIC_FONT));
}

void AssetManager::loadTexture() {
    _textureAsset.emplace(LAVA, std::make_shared<Raylib::Texture>(LAVA, 0, 0, WHITE));
    _textureAsset.emplace(BOMB_TEXTURE, std::make_shared<Raylib::Texture>(BOMB_TEXTURE, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE, std::make_shared<Raylib::Texture>(GUY_TEXTURE, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE_1, std::make_shared<Raylib::Texture>(GUY_TEXTURE_1, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE_2, std::make_shared<Raylib::Texture>(GUY_TEXTURE_2, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE_3, std::make_shared<Raylib::Texture>(GUY_TEXTURE_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_BACKGROUND, std::make_shared<Raylib::Texture>(MENU_BACKGROUND, 0, 0, WHITE));
    _textureAsset.emplace(MENU_HOW_1, std::make_shared<Raylib::Texture>(MENU_HOW_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_HOW_2, std::make_shared<Raylib::Texture>(MENU_HOW_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_HOW_3, std::make_shared<Raylib::Texture>(MENU_HOW_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_LOAD_1, std::make_shared<Raylib::Texture>(MENU_LOAD_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_LOAD_2, std::make_shared<Raylib::Texture>(MENU_LOAD_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_LOAD_3, std::make_shared<Raylib::Texture>(MENU_LOAD_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_START_1, std::make_shared<Raylib::Texture>(MENU_START_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_START_2, std::make_shared<Raylib::Texture>(MENU_START_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_START_3, std::make_shared<Raylib::Texture>(MENU_START_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_QUIT_1, std::make_shared<Raylib::Texture>(MENU_QUIT_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_QUIT_2, std::make_shared<Raylib::Texture>(MENU_QUIT_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_QUIT_3, std::make_shared<Raylib::Texture>(MENU_QUIT_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_UP_1, std::make_shared<Raylib::Texture>(MENU_UP_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_UP_2, std::make_shared<Raylib::Texture>(MENU_UP_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_UP_3, std::make_shared<Raylib::Texture>(MENU_UP_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_DOWN_1, std::make_shared<Raylib::Texture>(MENU_DOWN_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_DOWN_2, std::make_shared<Raylib::Texture>(MENU_DOWN_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_DOWN_3, std::make_shared<Raylib::Texture>(MENU_DOWN_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_HOW_TO_PLAY, std::make_shared<Raylib::Texture>(MENU_HOW_TO_PLAY, 0, 0, WHITE));
    _textureAsset.emplace(MENU_NEW_1, std::make_shared<Raylib::Texture>(MENU_NEW_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_NEW_2, std::make_shared<Raylib::Texture>(MENU_NEW_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_NEW_3, std::make_shared<Raylib::Texture>(MENU_NEW_3, 0, 0, WHITE));
    _textureAsset.emplace(MENU_MENU_1, std::make_shared<Raylib::Texture>(MENU_MENU_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_MENU_2, std::make_shared<Raylib::Texture>(MENU_MENU_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_MENU_3, std::make_shared<Raylib::Texture>(MENU_MENU_3, 0, 0, WHITE));
    _textureAsset.emplace(HUD_1, std::make_shared<Raylib::Texture>(HUD_1, 0, 0, WHITE));
    _textureAsset.emplace(HUD_2, std::make_shared<Raylib::Texture>(HUD_2, 0, 0, WHITE));
    _textureAsset.emplace(HUD_3, std::make_shared<Raylib::Texture>(HUD_3, 0, 0, WHITE));
    _textureAsset.emplace(HUD_4, std::make_shared<Raylib::Texture>(HUD_4, 0, 0, WHITE));
    _textureAsset.emplace(MOINS_START_1, std::make_shared<Raylib::Texture>(MOINS_START_1, 0, 0, WHITE));
    _textureAsset.emplace(PLUS_START_1, std::make_shared<Raylib::Texture>(PLUS_START_1, 0, 0, WHITE));
    _textureAsset.emplace(WALL_WOOD, std::make_shared<Raylib::Texture>(WALL_WOOD, 0, 0, WHITE));
    _textureAsset.emplace(WALL_UNBREAKABLE, std::make_shared<Raylib::Texture>(WALL_UNBREAKABLE, 0, 0, WHITE));
    _textureAsset.emplace(WALL_GRID, std::make_shared<Raylib::Texture>(WALL_GRID, 0, 0, WHITE));
    _textureAsset.emplace(WALL_ROCK, std::make_shared<Raylib::Texture>(WALL_ROCK, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE_1, std::make_shared<Raylib::Texture>(GUY_TEXTURE_1, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE_2, std::make_shared<Raylib::Texture>(GUY_TEXTURE_2, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE_3, std::make_shared<Raylib::Texture>(GUY_TEXTURE_3, 0, 0, WHITE));
    _textureAsset.emplace(GUY_TEXTURE_4, std::make_shared<Raylib::Texture>(GUY_TEXTURE_4, 0, 0, WHITE));
    _textureAsset.emplace(MENU_RESUME_1, std::make_shared<Raylib::Texture>(MENU_RESUME_1, 0, 0, WHITE));
    _textureAsset.emplace(MENU_RESUME_2, std::make_shared<Raylib::Texture>(MENU_RESUME_2, 0, 0, WHITE));
    _textureAsset.emplace(MENU_RESUME_3, std::make_shared<Raylib::Texture>(MENU_RESUME_3, 0, 0, WHITE));

}


void AssetManager::loadAudio() {
    _soundAsset.emplace(SOUND_BOING, std::make_shared<Raylib::Sound>(SOUND_BOING));
    _soundAsset.emplace(SOUND_EXPLOSION, std::make_shared<Raylib::Sound>(SOUND_EXPLOSION));
    _soundAsset.emplace(SOUND_WICK, std::make_shared<Raylib::Sound>(SOUND_WICK));
    _soundAsset.emplace(MENU_SOUND, std::make_shared<Raylib::Sound>(MENU_SOUND));

}

void AssetManager::loadColor() {
    _colorAsset.emplace(C_WHITE, std::make_shared<Raylib::ColorRGB>(0, 0, 0, 255));
    _colorAsset.emplace(C_BLUE, std::make_shared<Raylib::ColorRGB>(0, 0, 255, 255));
    _colorAsset.emplace(C_BLACK, std::make_shared<Raylib::ColorRGB>(255, 255, 255, 255));
    _colorAsset.emplace(C_GREEN, std::make_shared<Raylib::ColorRGB>(0, 255, 0, 255));
    _colorAsset.emplace(C_RED, std::make_shared<Raylib::ColorRGB>(255, 0, 0, 255));
    _colorAsset.emplace(C_BLANK, std::make_shared<Raylib::ColorRGB>(0, 0, 0, 0));
}

AssetManager::AssetManager() {
    loadingAsset();
}

AssetManager *AssetManager::getInstance() {
    if (_instance == nullptr)
        _instance = new AssetManager();
    return _instance;
}
