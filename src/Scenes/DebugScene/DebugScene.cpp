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
    /// ENTITIES - CREATION
    auto rect = this->createLocalEntity();
    _entityManager.addComponent<Component::Render2D>(rect,
        std::make_shared<raylib::Rectangle>((raylib::MyVector2){10, 10}, (raylib::MyVector2){20, 20})
    );
    auto block = this->createLocalEntity();
    _entityManager.addComponent<Component::Render3D>(block,
        std::make_shared<raylib::Cuboid>(nullptr, (raylib::MyVector3){50, 50, 0}, (raylib::MyVector3){50, 50, 50}, raylib::RColor::RRED)
    );
}

void DebugScene::update()
{
   auto render2D = _systemManager.getSystem<System::Render2DSystem>();
   auto render3D = _systemManager.getSystem<System::Render3DSystem>();

   render3D.update();
   render2D.update();
}
