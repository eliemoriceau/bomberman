#include "raylib.h"
#include "RenderSystem.hpp"
#include "ECSHandler.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"

void ECS::RenderSystem::update() {
    ECSHandler *ecsHandler = ECS::ECSHandler::getInstance();
    for (auto &entity : _entities) {

        auto render = ecsHandler->getComponent<ECS::RenderComponent>(entity);
        auto transform = ecsHandler->getComponent<ECS::TransformComponent>(entity);
        switch (render.renderType) {
            case ECS::RENDER_TYPE::CUBE:
                drawCube(render, transform);
                break;
            case ECS::RENDER_TYPE::SPHERE:
                drawSphere(render, transform);
                break;
            case ECS::RENDER_TYPE::MODEL:
                drawModel(render, transform);
                break;
            default:
                break;
        }
    }
}

void ECS::RenderSystem::drawCube(const RenderComponent &render, const TransformComponent &transform) {
    if (render.texture != nullptr)
        DrawCubeTexture(render.texture->getTexture(), transform.position->getVector(), render.size->x, render.size->y,
                        render.size->z, render.texture->getColor());
    else
        DrawCube(transform.position->getVector(), render.size->x, render.size->y, render.size->z,
                 render.color->getColor());

    DrawCubeWires(transform.position->getVector(), render.size->x, render.size->y, render.size->z, GRAY);
}

void ECS::RenderSystem::drawSphere(const RenderComponent &render, const TransformComponent &transform) {
    DrawSphere(transform.position->getVector(), render.size->x, render.color->getColor());
}

void ECS::RenderSystem::drawModel(const RenderComponent &render, const TransformComponent &transform) {
    render.model->setPosition(transform.position->getVector());
    render.model->setRotation(transform.rotation_axes->getVector());
    render.model->drawModel();
}
