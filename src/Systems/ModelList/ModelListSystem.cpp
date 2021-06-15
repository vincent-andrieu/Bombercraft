/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render3DSystem.cpp.cc
*/

#include "ModelListSystem.hpp"
#include "Game/CoreData/CoreData.hpp"

using namespace System;

System::ModelListSystem::ModelListSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::ModelList>();
}

void System::ModelListSystem::update()
{
    Game::CoreData::camera->begin3D();
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto [render] = Game::CoreData::entityManager->getComponents<Component::ModelList>(entity);

        render.draw();
    }
    Game::CoreData::camera->end3D();
}
