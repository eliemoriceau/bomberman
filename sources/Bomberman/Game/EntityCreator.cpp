//
// Created by marin on 14/06/2021.
//

#include "RemovableComponent.hpp"
#include "EntityCreator.hpp"
#include "AssetManager.hpp"
#include "AIComponent.hpp"

ECS::Entity EntityCreator::createBomberUp(const std::shared_ptr<Raylib::Vector3> &pos) {
    auto ecsHandler = ECS::ECSHandler::getInstance();
    auto mapManager = MapManager::getInstance();
    auto asset = AssetManager::getInstance();

    auto cube = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto size = newVector(0.5f, 0.5f, 0.5f);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());

    ECS::TransformComponent transform = {pos, old, axes};
    ECS::PickableComponent pickableComponent = {ECS::BOMBER_UP, size};
    ECS::RenderComponent render = {ECS::CUBE, size, nullptr, asset->getColor(C_BLUE), nullptr};

    ecsHandler->addComponent(cube, transform);
    ecsHandler->addComponent(cube, render);
    ecsHandler->addComponent(cube, pickableComponent);

    mapManager->addBonus(cube);

    return cube;
}

ECS::Entity EntityCreator::createFireUp(const std::shared_ptr<Raylib::Vector3> &pos) {
    auto ecsHandler = ECS::ECSHandler::getInstance();
    auto mapManager = MapManager::getInstance();
    auto asset = AssetManager::getInstance();

    auto cube = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto size = newVector(0.5f, 0.5f, 0.5f);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());

    ECS::TransformComponent transform = {pos, old, axes};
    ECS::PickableComponent pickableComponent = {ECS::FIRE_UP, size};
    ECS::RenderComponent render = {ECS::CUBE, size, nullptr, asset->getColor(C_GREEN), nullptr};

    ecsHandler->addComponent(cube, transform);
    ecsHandler->addComponent(cube, render);
    ecsHandler->addComponent(cube, pickableComponent);

    mapManager->addBonus(cube);
    return cube;
}

ECS::Entity EntityCreator::createSpeedUp(const std::shared_ptr<Raylib::Vector3> &pos) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto mapManager = MapManager::getInstance();
    auto asset = AssetManager::getInstance();

    auto cube = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto size = newVector(0.5f, 0.5f, 0.5f);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());

    ECS::TransformComponent transform = {pos, old, axes};
    ECS::PickableComponent pickableComponent = {ECS::SPEED_UP, size};
    ECS::RenderComponent render = {ECS::CUBE, size, nullptr, asset->getColor(C_RED), nullptr};

    ecsHandler->addComponent(cube, transform);
    ecsHandler->addComponent(cube, render);
    ecsHandler->addComponent(cube, pickableComponent);

    mapManager->addBonus(cube);

    return cube;
}

ECS::Entity
EntityCreator::createCube(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                          std::shared_ptr<Raylib::ColorRGB> color, const std::string &texture_name, int x, int y) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto cube = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());
    auto asset = AssetManager::getInstance();

    ECS::TransformComponent transform = {pos, old, axes, std::make_shared<int>(x), std::make_shared<int>(y), 'O'};
    ECS::ColliderComponent collider = {ECS::CUBE_COLLIDER, size};
    ECS::RenderComponent render = {ECS::CUBE, size, nullptr, std::move(color),
                                   std::move(asset->getTexture(texture_name))};

    ecsHandler->addComponent(cube, transform);
    ecsHandler->addComponent(cube, render);
    ecsHandler->addComponent(cube, collider);

    return cube;
}

ECS::Entity
EntityCreator::createPlayer(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                            const std::vector<KeyboardKey> &inputs, float speed, const std::string &player_model,
                            std::pair<int, int> map_pos, char id) {
    auto ecsHandler = ECS::ECSHandler::getInstance();
    auto assetManager = AssetManager::getInstance();
    auto player = ecsHandler->createEntity();

    auto color = std::make_shared<Raylib::ColorRGB>(255, 255, 255, 255);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());
    auto axes = newVector(1.0f, 0.0f, 90.0f);
    auto playerModel = assetManager->getModel(player_model);


    ECS::TransformComponent transform = {pos, old, axes, std::make_shared<int>(map_pos.first),
                                         std::make_shared<int>(map_pos.second), id, 'O'};
    ECS::ColliderComponent collider = {ECS::PLAYER_COLLIDER, size};
    ECS::RenderComponent render = {ECS::MODEL, size, playerModel, color};
    ECS::HealthComponent health = {std::make_shared<int>(1)};
    ECS::ControllableComponent move = {inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5],
                                       std::make_shared<float>(speed), std::make_shared<double>(1.5),
                                       std::chrono::steady_clock::now(), std::make_shared<int>(1),
                                       assetManager->getSound(SOUND_BOING), std::make_shared<int>(0)};
    ECS::PickableComponent pickable = {ECS::PLAYER, size};

    ecsHandler->addComponent(player, transform);
    ecsHandler->addComponent(player, render);
    ecsHandler->addComponent(player, collider);
    ecsHandler->addComponent(player, health);
    ecsHandler->addComponent(player, pickable);
    ecsHandler->addComponent(player, move);

    return player;
}

ECS::Entity
EntityCreator::createAi(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                        float speed, const std::string &player_model, std::pair<int, int> map_pos, char id) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto assetManager = AssetManager::getInstance();
    auto player = ecsHandler->createEntity();
    auto playerModel = assetManager->getModel(player_model);

    auto color = std::make_shared<Raylib::ColorRGB>(255, 255, 255, 255);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto sound = std::make_shared<Raylib::Sound>(SOUND_BOING);


    ECS::TransformComponent transform = {pos, old, axes, std::make_shared<int>(map_pos.first), std::make_shared<int>(map_pos.second), id};
    ECS::ColliderComponent collider = {ECS::PLAYER_COLLIDER, size};
    ECS::RenderComponent render = {ECS::MODEL, size, playerModel, color};
    ECS::HealthComponent health = {std::make_shared<int>(1)};
    ECS::PickableComponent pickable = {ECS::PLAYER, size};
    ECS::ControllableComponent move = {KEY_B, KEY_B, KEY_B, KEY_B, KEY_B, KEY_B,
                                       std::make_shared<float>(speed), std::make_shared<double>(1.5),
                                       std::chrono::steady_clock::now(), std::make_shared<int>(1),
                                       assetManager->getSound(SOUND_BOING), std::make_shared<int>(1)};
    ECS::AIComponent ai = {newVector(-1, 1.1, -1), std::make_shared<int>(0),std::make_shared<int>(0), std::make_shared<int>(0), std::make_shared<int>(0), std::make_shared<int>(0), std::make_shared<int>(0), std::make_shared<int>(0), std::make_shared<Timer>(), std::make_shared<std::deque<std::shared_ptr<Raylib::Vector3>>>() };

    ecsHandler->addComponent(player, transform);
    ecsHandler->addComponent(player, render);
    ecsHandler->addComponent(player, collider);
    ecsHandler->addComponent(player, health);
    ecsHandler->addComponent(player, pickable);
    ecsHandler->addComponent(player, ai);
    ecsHandler->addComponent(player, move);

    return player;
}

ECS::Entity
EntityCreator::createText(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                          const std::string &title) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto text_entity = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto asset = AssetManager::getInstance();
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());
    auto text = std::make_shared<Raylib::Text>(title, asset->getFont(BASIC_FONT), Raylib::Vector2(pos->x, pos->y),
                                               (int) size->x);

    ECS::TransformComponent transform = {pos, old, axes};
    ECS::Render2dComponent comp = {ECS::TEXT, nullptr, text, nullptr, std::make_shared<bool>(false)};
    ecsHandler->addComponent(text_entity, transform);
    ecsHandler->addComponent(text_entity, comp);

    return (text_entity);
}

ECS::Entity
EntityCreator::createTexture(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                             const std::string &path) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto hud = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());
    auto asset = AssetManager::getInstance();

    ECS::TransformComponent transform = {pos, old, axes};
    ECS::Render2dComponent comp = {ECS::TEXTURE, asset->getTexture(path), nullptr, nullptr, std::make_shared<bool>(false)};
    ecsHandler->addComponent(hud, transform);
    ecsHandler->addComponent(hud, comp);

    return (hud);
}

ECS::Entity EntityCreator::createCubeBreakable(const std::shared_ptr<Raylib::Vector3> &pos,
                                               const std::shared_ptr<Raylib::Vector3> &size,
                                               std::shared_ptr<Raylib::ColorRGB> color,
                                               std::shared_ptr<Raylib::Texture> texture) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    auto cube = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    std::shared_ptr<Raylib::Vector3> old = newVector(pos->getX(), pos->getY(), pos->getZ());
    ECS::TransformComponent transform = {pos, old, axes};
    ECS::ColliderComponent collider = {ECS::CUBE_COLLIDER, size};
    ECS::RenderComponent render = {ECS::CUBE, size, nullptr, std::move(color), std::move(texture)};

    ecsHandler->addComponent(cube, transform);
    ecsHandler->addComponent(cube, render);
    ecsHandler->addComponent(cube, collider);

    return cube;
}

ECS::Entity EntityCreator::createBomb(const std::shared_ptr<Raylib::Vector3> &pos, int range) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto asset = AssetManager::getInstance();
    auto mapManager = MapManager::getInstance();

    auto grid_pos = MapManager::getInstance()->getGridPosition(pos);
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto cube = ecsHandler->createEntity();
    auto size = newVector(0.5f, 0.5f, 0.5f);
    auto timer = std::make_shared<Timer>();

    timer->start();
    ECS::BombComponent bombComponent = {3, timer, false, 15, 0, range, asset->getSound(SOUND_EXPLOSION),
                                        asset->getSound(SOUND_WICK)};
    ECS::TransformComponent transform = {
            std::make_shared<Raylib::Vector3>(grid_pos->getX(), grid_pos->getY(), grid_pos->getZ()),
            std::make_shared<Raylib::Vector3>(grid_pos->getX(), grid_pos->getY(), grid_pos->getZ()),
            axes
    };
    ECS::RenderComponent render = {ECS::MODEL, size, asset->getModel(BOMB_MODEL), asset->getColor(C_BLANK)};
    ECS::ColliderComponent collider = {ECS::BOMB_COLLIDER, size};


    ecsHandler->addComponent(cube, transform);
    ecsHandler->addComponent(cube, render);
    ecsHandler->addComponent(cube, bombComponent);
    ecsHandler->addComponent(cube, collider);

    mapManager->addBomb(cube);

    return cube;
}

ECS::Entity
EntityCreator::createSphere(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                            std::shared_ptr<Raylib::ColorRGB> color) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();
    auto sphere = ecsHandler->createEntity();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());

    ECS::TransformComponent transform = {pos, old, axes};
    ECS::ColliderComponent collider = {ECS::SPHERE_COLLIDER, size};
    ECS::RenderComponent render = {ECS::SPHERE, size, nullptr, std::move(color)};

    ecsHandler->addComponent(sphere, transform);
    ecsHandler->addComponent(sphere, render);
    ecsHandler->addComponent(sphere, collider);

    return sphere;
}

ECS::Entity EntityCreator::createExplosion(const std::shared_ptr<Raylib::Vector3> &pos) {
    auto *ecsHandler = ECS::ECSHandler::getInstance();

    auto cube = ecsHandler->createEntity();
    auto asset = AssetManager::getInstance();
    auto axes = newVector(1.0f, 0.0f, 0.0f);
    auto size = newVector(0.8f, 0.8f, 0.8f);
    auto old = newVector(pos->getX(), pos->getY(), pos->getZ());
    auto timer = std::make_shared<Timer>();
    timer->start();

    ECS::TransformComponent transform = {pos, old, axes, std::make_shared<int>((int) pos->getX()),
                                         std::make_shared<int>((int) pos->getY())};
    ECS::RenderComponent render = {ECS::CUBE, size, nullptr, asset->getColor(C_BLANK), asset->getTexture(LAVA)};
    ECS::RemovableComponent remove = {500, timer};

    ecsHandler->addComponent(cube, transform);
    ecsHandler->addComponent(cube, remove);
    ecsHandler->addComponent(cube, render);

    return cube;
}
