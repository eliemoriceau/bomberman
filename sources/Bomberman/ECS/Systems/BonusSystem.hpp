/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#pragma once

#include "System.hpp"

#define NB_BONUS 3

namespace ECS {
    class BonusSystem : public ECS::System {
    public:
        static void drop(std::shared_ptr<Raylib::Vector3> &pos);

        static void bombUp(std::shared_ptr<Raylib::Vector3> &pos);

        static void speedUp(std::shared_ptr<Raylib::Vector3> &pos);

        static void fireUp(std::shared_ptr<Raylib::Vector3> &pos);

        static bool probToDrop(float percentage);

        static void selectBonus(std::shared_ptr<Raylib::Vector3> &pos);
    };
}


