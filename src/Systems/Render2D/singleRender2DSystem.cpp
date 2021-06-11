/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 singleRender2DSystem.cpp.cc
*/

#include "Game/Core/Core.hpp"
#include "singleRender2DSystem.hpp"

System::singleRender2DSystem::singleRender2DSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::SingleRender2D>();
}

void System::singleRender2DSystem::update()
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto [singleRender] = Game::CoreData::entityManager->getComponents<Component::SingleRender2D>(entity);
        singleRender.draw();
    }
}