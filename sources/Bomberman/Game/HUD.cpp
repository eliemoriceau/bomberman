//
// Created by marin on 16/06/2021.
//

#include "HUD.hpp"

HUD *HUD::_instance = nullptr;

HUD *HUD::getInstance() {
    if (_instance == nullptr)
        _instance = new HUD();
    return _instance;
}

void HUD::updateHubPropertiesSpeed(int index) {
    std::shared_ptr<HUD_Properties> properties = _hubProperties[index];

    properties->level_1 = properties->level_1 + 1;

    updateHubProperties(index);
}

void HUD::updateHubPropertiesFire(int index) {
    std::shared_ptr<HUD_Properties> properties = _hubProperties[index];

    properties->level_2 = properties->level_2 + 1;

    updateHubProperties(index);
}

void HUD::updateHubPropertiesUp(int index) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto player = PlayerManager::getInstance()->getPlayerById(index);
    auto bomb = ecsHandler->getComponent<ECS::ControllableComponent>(player);

    std::shared_ptr<HUD_Properties> properties = _hubProperties[index];

    std::chrono::steady_clock::time_point tmp = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
            tmp - bomb.timeLastDrop);

    if (!PlayerManager::getInstance()->isPlayerDead(player)) {
        if (time_span.count() >= *bomb.timerDrop) {
            ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setColor(GREEN);
        } else {
            ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setColor(RED);
        }
    }


    properties->level_3 = properties->level_3 + 1;

    updateHubProperties(index);
}

void HUD::updateHubProperties(int index) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    std::shared_ptr<HUD_Properties> properties = _hubProperties[index];

    ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setText(
            std::to_string(properties->level_3));

    ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_1).text->setText(
            std::to_string(properties->level_1));
    ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_2).text->setText(
            std::to_string(properties->level_2));
    ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setText(
            std::to_string(properties->level_3));
}

HUD_Properties HUD::createHubProperties(const std::shared_ptr<Raylib::Vector3> &pos, const std::string &texture,
                                        const std::string &name) {
    HUD_Properties properties{};

    properties.texture = EntityCreator::createTexture(pos, newVector(1, 1, 1), texture);
    properties.text_name = EntityCreator::createText(newVector(pos->x + 30, pos->y + 112, 1), newVector(30, 1, 1),
                                                     name);

    properties.bonus_1 = EntityCreator::createText(newVector(pos->x + 140, pos->y + 9, 1), newVector(25, 1, 1), "0");
    properties.bonus_2 = EntityCreator::createText(newVector(pos->x + 140, pos->y + 48, 1), newVector(25, 1, 1), "0");
    properties.bonus_3 = EntityCreator::createText(newVector(pos->x + 140, pos->y + 81, 1), newVector(25, 1, 1), "0");

    properties.level_1 = 0;
    properties.level_2 = 0;
    properties.level_3 = 0;

    return properties;
}

void HUD::updateHudAllPlayer() {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto players = PlayerManager::getInstance()->getPlayers();

    for (auto player : players) {
        if (!PlayerManager::getInstance()->isPlayerDead(player)) {
            auto transform = ecsHandler->getComponent<ECS::TransformComponent>(player);
            auto bomb = ecsHandler->getComponent<ECS::ControllableComponent>(player);
            std::shared_ptr<HUD_Properties> properties = _hubProperties[PlayerManager::getIndexByID(
                    transform.id)];

            std::chrono::steady_clock::time_point tmp = std::chrono::steady_clock::now();
            std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
                    tmp - bomb.timeLastDrop);

            auto timer = *bomb.timerDrop - time_span.count();
            if (time_span.count() >= *bomb.timerDrop) {
                ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setColor(GREEN);
                ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setText("0");
            } else {
                ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setColor(RED);
                ecsHandler->getComponent<ECS::Render2dComponent>(properties->bonus_3).text->setText(
                        std::to_string(timer).substr(0, 4));
            }
        }
    }

}

void HUD::createHUD() {
    std::vector<std::shared_ptr<Raylib::Vector3>> positions = {
            newVector(40, 50, 1),
            newVector(1690, 50, 1),
            newVector(1690, 880, 1),
            newVector(40, 880, 1)
    };

    std::vector<std::string> textures = {
            HUD_1,
            HUD_2,
            HUD_3,
            HUD_4
    };
    int index = 0;
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    for (auto pl : PlayerManager::getInstance()->getPlayers()) {
        auto transform = ecsHandler->getComponent<ECS::TransformComponent>(pl);
        std::string name = "Player ";
        name.append(std::to_string(PlayerManager::getIndexByID(transform.id) + 1));
        _hubProperties.push_back(
                std::make_shared<HUD_Properties>(createHubProperties(positions[index], textures[index], name)));
        index++;
    }
    displayHud(_hubProperties, true);
}

void HUD::clearHud() {
    _hubProperties.clear();
}

void HUD::displayHud(const std::vector<std::shared_ptr<HUD_Properties>>& properties, bool value)
{
    for (auto hud : properties) {
        *ECS::ECSHandler::getInstance()->getComponent<ECS::Render2dComponent>(hud->texture).enabled = value;
        *ECS::ECSHandler::getInstance()->getComponent<ECS::Render2dComponent>(hud->text_name).enabled = value;
        *ECS::ECSHandler::getInstance()->getComponent<ECS::Render2dComponent>(hud->bonus_1).enabled = value;
        *ECS::ECSHandler::getInstance()->getComponent<ECS::Render2dComponent>(hud->bonus_2).enabled = value;
        *ECS::ECSHandler::getInstance()->getComponent<ECS::Render2dComponent>(hud->bonus_3).enabled = value;
    }
}