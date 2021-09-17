/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include <string>
#include <map>
#include <Model.hpp>
#include <Color.hpp>
#include <Sound.hpp>
#include <Texture.hpp>
#include <Text.hpp>
#include <Button.hpp>

class AssetManager {
public:
    ~AssetManager() = default;

    static AssetManager *getInstance();

    void addModel(const std::string &name, const std::shared_ptr<Raylib::Model> &newModel);

    std::shared_ptr<Raylib::Model> getModel(const std::string &name);

    void addColor(const std::string &name, const std::shared_ptr<Raylib::ColorRGB> &newColor);

    std::shared_ptr<Raylib::ColorRGB> getColor(const std::string &name);

    void addSound(const std::string &name, const std::shared_ptr<Raylib::Sound> &newSound);

    std::shared_ptr<Raylib::Sound> getSound(const std::string &name);

    void addTexture(const std::string &name, const std::shared_ptr<Raylib::Texture> &newTexture);

    std::shared_ptr<Raylib::Texture> getTexture(const std::string &name);

    void addText(const std::string &name, const std::shared_ptr<Raylib::Text> &newText);

    std::shared_ptr<Raylib::Text> getText(const std::string &name);

    void addButton(const std::string &name, const std::shared_ptr<Raylib::Button> &newButton);

    std::shared_ptr<Raylib::Button> getButton(const std::string &name);

    void addFont(const std::string &name, const std::shared_ptr<Raylib::Font> &newFont);

    std::shared_ptr<Raylib::Font> getFont(const std::string &name);

    void loadingAsset();

private:
    static AssetManager *_instance;

    AssetManager();

    std::map<std::string, std::shared_ptr<Raylib::Model>> _modelAsset;
    std::map<std::string, std::shared_ptr<Raylib::ColorRGB>> _colorAsset;
    std::map<std::string, std::shared_ptr<Raylib::Sound>> _soundAsset;
    std::map<std::string, std::shared_ptr<Raylib::Texture>> _textureAsset;
    std::map<std::string, std::shared_ptr<Raylib::Text>> _textAsset;
    std::map<std::string, std::shared_ptr<Raylib::Button>> _buttonAsset;
    std::map<std::string, std::shared_ptr<Raylib::Font>> _fontAsset;

    void loadColor();

    void loadAudio();

    void loadTexture();

    void loadFonts();

    void loadModels();
};



