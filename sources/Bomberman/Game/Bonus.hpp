/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once


#include <Vector3.hpp>
#include <memory>
#include "EntityCreator.hpp"

class Bonus {
public:
    static void createBomberUp(const std::shared_ptr<Raylib::Vector3> &pos);

    static void createSpeedUp(const std::shared_ptr<Raylib::Vector3> &pos);

    static void createFireUp(const std::shared_ptr<Raylib::Vector3> &pos);
};



