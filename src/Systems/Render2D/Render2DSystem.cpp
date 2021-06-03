/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2DSystem.cpp.cc
*/

#include "Render2DSystem.hpp"

System::Render2DSystem::Render2DSystem(Engine::EntityManager &entityManager) : AbstractSystem(entityManager)
{
    this->setRequirements<Component::Render2D>();
}

void System::Render2DSystem::update()
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto [render] = _entityManager.getComponents<Component::Render2D>(entity);

        render.modele->draw();
    }
}
