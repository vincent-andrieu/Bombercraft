/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"

using namespace Game;

Core::Core() : CoreData(), globalEntities(*this->entityManager)
{
    /// COMPONENTS - DEFINITION
    CoreData::entityManager->registerComponent<Component::Render2D>();
    CoreData::entityManager->registerComponent<Component::Render3D>();
    CoreData::entityManager->registerComponent<Component::ClickEvent>();
    CoreData::entityManager->registerComponent<Component::KeyEvent>();
    CoreData::entityManager->registerComponent<Component::MouseMoveEvent>();
    CoreData::entityManager->registerComponent<Component::Hitbox>();
    CoreData::entityManager->registerComponent<Engine::Position>();
    CoreData::entityManager->registerComponent<Engine::Velocity>();
    /// SYSTEMS - CREATION
    CoreData::_systemManager->createSystem<System::Render3DSystem>();
    CoreData::_systemManager->createSystem<System::Render2DSystem>();
    CoreData::_systemManager->createSystem<System::ClickEventSystem>();
    CoreData::_systemManager->createSystem<System::KeyEventSystem>();
    CoreData::_systemManager->createSystem<System::MouseEventSystem>();
    CoreData::_systemManager->createSystem<Engine::PhysicsSystem>(*this->entityManager);
    CoreData::_systemManager->createSystem<System::HitboxSystem>();
    // SCENES - CREATION
    CoreData::sceneManager->createScene<DebugScene>(*this->_systemManager);
}

void Core::loop()
{
    this->_window.open();
    while (this->_window.isOpen()) {
        this->_window.clear();
        CoreData::sceneManager->run();
        this->_window.refresh();
    }
    this->_window.close();
}
