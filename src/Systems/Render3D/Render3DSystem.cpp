/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render3DSystem.cpp.cc
*/

#include "Render3DSystem.hpp"

System::Render3DSystem::Render3DSystem(Engine::EntityManager &entityManager) : AbstractSystem(entityManager)
{
    this->setRequirements<Component::Render3D>();
}

void System::Render3DSystem::update()
{
    Game::Core::camera->begin3D();
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto [render] = _entityManager.getComponents<Component::Render3D>(entity);

        render.modele->draw();
    }
    Game::Core::camera->end3D();
}
