/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include <random>
#include "Bonus.hpp"
#include "ECSHandler.hpp"
#include "BonusSystem.hpp"
#include "VectorUtils.hpp"

void ECS::BonusSystem::drop(std::shared_ptr<Raylib::Vector3> &pos) {

    if (probToDrop(20))
        selectBonus(pos);
}

bool ECS::BonusSystem::probToDrop(float percentage) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 100);
    int prob = uniform_dist(e1);
    if (prob <= percentage)
        return true;
    return false;
}

void ECS::BonusSystem::selectBonus(std::shared_ptr<Raylib::Vector3> &pos) {
    MapManager *map_manager = MapManager::getInstance();
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, NB_BONUS);
    int bonus = uniform_dist(e1);
    auto new_pos = MapManager::getInstance()->getGridPosition(pos);


    switch (bonus) {
        case 1:
            bombUp(new_pos);
            break;
        case 2:
            speedUp(new_pos);
            break;
        case 3:
            fireUp(new_pos);
            break;
        default:
            std::cout << "Error Bonus drop" << std::endl;
            break;
    }
    auto coords = MapManager::getInstance()->getArrayCoords(new_pos);
    map_manager->setMapCoord(coords.first, coords.second, 'P');
}

void ECS::BonusSystem::bombUp(std::shared_ptr<Raylib::Vector3> &pos) {
    Bonus::createBomberUp(pos);
}

void ECS::BonusSystem::speedUp(std::shared_ptr<Raylib::Vector3> &pos) {
    Bonus::createSpeedUp(pos);
}

void ECS::BonusSystem::fireUp(std::shared_ptr<Raylib::Vector3> &pos) {
    Bonus::createFireUp(pos);
}
