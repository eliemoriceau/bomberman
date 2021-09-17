/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "VectorUtils.hpp"
#include "Bonus.hpp"

void Bonus::createBomberUp(const std::shared_ptr<Raylib::Vector3> &pos) {
    MapManager::getInstance()->addBonus(EntityCreator::createBomberUp(pos));
}

void Bonus::createSpeedUp(const std::shared_ptr<Raylib::Vector3> &pos) {
    MapManager::getInstance()->addBonus(EntityCreator::createSpeedUp(pos));
}

void Bonus::createFireUp(const std::shared_ptr<Raylib::Vector3> &pos) {
    MapManager::getInstance()->addBonus(EntityCreator::createFireUp(pos));
}
