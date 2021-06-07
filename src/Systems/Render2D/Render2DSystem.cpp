/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2DSystem.cpp.cc
*/

#include "Render2DSystem.hpp"
#include "Game/Core/Core.hpp"

System::Render2DSystem::Render2DSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::Render2D>();
}

void System::Render2DSystem::update()
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto [render] = Game::CoreData::entityManager->getComponents<Component::Render2D>(entity);

        render.modele->draw();
    }
}
