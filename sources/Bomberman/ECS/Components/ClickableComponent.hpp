/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/
#pragma once

namespace ECS {
    struct ClickableComponent {
        Rectangle recBox{};

        void (*callback)(){};
    };
}
