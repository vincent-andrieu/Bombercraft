/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.cpp.cc
*/

#include "DebugScene.hpp"

using namespace Game;

DebugScene::DebugScene(Engine::SystemManager &systemManager, Engine::EntityManager &entityManager)
    : AbstractScene(systemManager, entityManager)
{
}

void DebugScene::update()
{
   auto render2D = _systemManager.getSystem<System::Render2DSystem>();
   auto render3D = _systemManager.getSystem<System::Render3DSystem>();

   render3D.update();
   render2D.update();
}
