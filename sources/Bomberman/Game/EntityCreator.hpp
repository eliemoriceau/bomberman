//
// Created by marin on 14/06/2021.
//
#pragma once

#include "Vector3.hpp"
#include "ECSHandler.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "VectorUtils.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "RenderComponent.hpp"
#include "BombComponent.hpp"
#include "DefineResources.hpp"
#include "HealthComponent.hpp"
#include "ControllableComponents.hpp"
#include "PickableComponent.hpp"
#include "MapManager.hpp"
#include "ECSHandler.hpp"
#include "Entity.hpp"
#include <algorithm>
#include "Render2dComponent.hpp"
#include "Text.hpp"

class EntityCreator {
public:
    static ECS::Entity
    createText(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
               const std::string &title);

    static ECS::Entity
    createTexture(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                  const std::string &path);

    static ECS::Entity
    createCube(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
               std::shared_ptr<Raylib::ColorRGB> color, const std::string &texture_name, int x, int y);

    static ECS::Entity
    createSphere(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                 std::shared_ptr<Raylib::ColorRGB> color);

    static ECS::Entity createBomb(const std::shared_ptr<Raylib::Vector3> &pos, int range);

    static ECS::Entity
    createCubeBreakable(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                        std::shared_ptr<Raylib::ColorRGB> color, std::shared_ptr<Raylib::Texture> texture);

    static ECS::Entity createSpeedUp(const std::shared_ptr<Raylib::Vector3> &pos);

    static ECS::Entity createFireUp(const std::shared_ptr<Raylib::Vector3> &pos);

    static ECS::Entity createBomberUp(const std::shared_ptr<Raylib::Vector3> &pos);

    static ECS::Entity
    createPlayer(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
                 const std::vector<KeyboardKey> &inputs, float speed, const std::string &player_model,
                 std::pair<int, int> map_pos, char id);

    static ECS::Entity createAi(const std::shared_ptr<Raylib::Vector3> &pos, const std::shared_ptr<Raylib::Vector3> &size,
             float speed, const std::string &player_model, std::pair<int, int> map_pos, char id);

    static ECS::Entity createExplosion(const std::shared_ptr<Raylib::Vector3> &pos);
};
