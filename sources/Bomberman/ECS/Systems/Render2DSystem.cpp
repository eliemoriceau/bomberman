/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by elie,
*/

#include "ECSHandler.hpp"
#include "Render2dComponent.hpp"
#include "Render2DSystem.hpp"
#include "raylib.h"
#include "TransformComponent.hpp"

void ECS::Render2dSystem::update() {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    for (auto &entity : _entities) {
        auto render = ecsHandler->getComponent<ECS::Render2dComponent>(entity);
        auto transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);

        if (*render.enabled) {
            switch (render.type) {
                case ECS::RENDER_2D_TYPE::TEXTURE:
                    drawTexture(render, transform);
                    break;
                case ECS::RENDER_2D_TYPE::TEXT:
                    drawText(render, transform);
                    break;
                case ECS::RENDER_2D_TYPE::BUTTON:
                    drawButton(render, transform);
                    break;
                default:
                    break;
            }
        }
    }
}

void ECS::Render2dSystem::drawText(const ECS::Render2dComponent &render, const ECS::TransformComponent &transform) {
    DrawText(render.text->getText().c_str(), render.text->getPos().getX(), render.text->getPos().getY(),
             render.text->getSize(), render.text->getColor());
}

void ECS::Render2dSystem::drawTexture(const ECS::Render2dComponent &render, const ECS::TransformComponent &transform) {
    Rectangle _sourceRec = {0, 0, (float) render.texture->getTexture().width,
                            (float) render.texture->getTexture().height};
    DrawTextureRec(render.texture->getTexture(), _sourceRec, {transform.position->x, transform.position->y}, WHITE);
}

void ECS::Render2dSystem::drawButton(const ECS::Render2dComponent &render, const ECS::TransformComponent &transform) {
    DrawTextureRec(render.button->getTexture(), render.button->getSourceRec(),
                   {render.button->getX(), render.button->getY()}, WHITE);
    render.button->manageButtonInterract();
}