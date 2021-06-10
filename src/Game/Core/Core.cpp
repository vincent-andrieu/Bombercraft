/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Components/Chrono/Chrono.hpp"

using namespace Game;

Core::Core() : CoreData(), globalEntities(*CoreData::entityManager)
{
    CoreData::_window->open();
    /// COMPONENTS - DEFINITION
    CoreData::entityManager->registerComponent<Component::Render2D>();
    CoreData::entityManager->registerComponent<Component::Render3D>();
    CoreData::entityManager->registerComponent<Component::ClickEvent>();
    CoreData::entityManager->registerComponent<Component::ClickFocusEvent>();
    CoreData::entityManager->registerComponent<Component::KeyEvent>();
    CoreData::entityManager->registerComponent<Component::MouseMoveEvent>();
    CoreData::entityManager->registerComponent<Component::Hitbox>();
    CoreData::entityManager->registerComponent<Engine::Position>();
    CoreData::entityManager->registerComponent<Component::KeyBox>();
    //Component::
    CoreData::entityManager->registerComponent<Engine::Velocity>();
    CoreData::entityManager->registerComponent<Engine::Timer>();
    CoreData::entityManager->registerComponent<Engine::Script>();
    CoreData::entityManager->registerComponent<Component::Chrono>();
    CoreData::entityManager->registerComponent<Component::TextInputConfig>();
    /// SYSTEMS - CREATION
    CoreData::_systemManager->createSystem<System::Render3DSystem>();
    CoreData::_systemManager->createSystem<System::Render2DSystem>();
    CoreData::_systemManager->createSystem<System::ClickEventSystem>();
    CoreData::_systemManager->createSystem<System::KeyEventSystem>();
    CoreData::_systemManager->createSystem<System::MouseEventSystem>();
    CoreData::_systemManager->createSystem<System::ClickFocusSystem>();
    CoreData::_systemManager->createSystem<Engine::TimerSystem>(*CoreData::entityManager);
    CoreData::_systemManager->createSystem<System::PhysicsSystem>();
    CoreData::_systemManager->createSystem<System::HitboxSystem>();
    // SCENES - CREATION
    CoreData::sceneManager->createScene<DebugScene>((*CoreData::_systemManager));
    CoreData::sceneManager->createScene<MainMenuScene>((*CoreData::_systemManager));
    CoreData::sceneManager->setScene<DebugScene>();
}

void Core::loop()
{
    while (CoreData::_window->isOpen()) {
        CoreData::_window->clear();
        CoreData::sceneManager->run();
        CoreData::_window->refresh();
    }
    CoreData::_window->close();
}
