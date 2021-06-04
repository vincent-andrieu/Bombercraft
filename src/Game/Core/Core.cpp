/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"

using namespace Game;

Core::Core() : CoreData(), globalEntities(*CoreData::entityManager)
{
    /// COMPONENTS - DEFINITION
    CoreData::entityManager->registerComponent<Component::Render2D>();
    CoreData::entityManager->registerComponent<Component::Render3D>();
    CoreData::entityManager->registerComponent<Component::ClickEvent>();
    CoreData::entityManager->registerComponent<Component::KeyEvent>();
    CoreData::entityManager->registerComponent<Component::MouseMoveEvent>();
    /// SYSTEMS - CREATION
    CoreData::_systemManager->createSystem<System::Render3DSystem>(*CoreData::entityManager);
    CoreData::_systemManager->createSystem<System::Render2DSystem>(*CoreData::entityManager);
    CoreData::_systemManager->createSystem<System::ClickEventSystem>(*CoreData::entityManager);
    CoreData::_systemManager->createSystem<System::KeyEventSystem>(*CoreData::entityManager);
    CoreData::_systemManager->createSystem<System::MouseEventSystem>(*CoreData::entityManager);
    // SCENES - CREATION
    CoreData::sceneManager->createScene<DebugScene>((*CoreData::_systemManager), (*CoreData::entityManager), (*CoreData::eventManager));
}

Core::~Core()
{
}

void Core::loop()
{
    _window.open();
    while (_window.isOpen()) {
        _window.clear();
        CoreData::sceneManager->run();
        _window.refresh();
    }
    _window.close();
}
