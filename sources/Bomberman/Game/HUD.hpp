//
// Created by marin on 16/06/2021.
//

#pragma once

#include "Text.hpp"
#include "Texture.hpp"
#include "Entity.hpp"
#include <vector>
#include "Vector3.hpp"
#include "Render2dComponent.hpp"
#include "PlayerManager.hpp"
#include "TransformComponent.hpp"

class HUD_Properties {
public:
    ECS::Entity texture;
    ECS::Entity text_name;
    ECS::Entity bonus_1;
    ECS::Entity bonus_2;
    ECS::Entity bonus_3;
    int level_1;
    int level_2;
    int level_3;
};

class HUD {
public:
    ~HUD() = default;

    static HUD *getInstance();

    void createHUD();

    void updateHubPropertiesSpeed(int index);

    void updateHubPropertiesFire(int index);

    void updateHubPropertiesUp(int index);

    void updateHubProperties(int index);

    static HUD_Properties createHubProperties(const std::shared_ptr<Raylib::Vector3> &pos, const std::string &texture,
                                              const std::string &name);

    void updateHudAllPlayer();

    void clearHud();

    void displayHud(const std::vector<std::shared_ptr<HUD_Properties>>& properties, bool value);

private:
    HUD() = default;

    std::vector<std::shared_ptr<HUD_Properties>> _hubProperties;
    static HUD *_instance;

};