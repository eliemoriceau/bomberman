/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/
#pragma once

#include <Timer.hpp>
#include <memory>

namespace ECS {
    struct RemovableComponent {
        double time;
        std::shared_ptr<Timer> timer;
    };
}
