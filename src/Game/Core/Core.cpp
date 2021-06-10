/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Components/Chrono/Chrono.hpp"
#include "Components/Sound/Sound.hpp"
#include "Components/Music/Music.hpp"
#include "Systems/Music/MusicSystem.hpp"
#include "Systems/Sound/SoundSystem.hpp"

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
    CoreData::entityManager->registerComponent<Engine::Velocity>();
    CoreData::entityManager->registerComponent<Engine::Timer>();
    CoreData::entityManager->registerComponent<Engine::Script>();
    CoreData::entityManager->registerComponent<Component::Chrono>();
    CoreData::entityManager->registerComponent<Component::TextInputConfig>();
    CoreData::entityManager->registerComponent<Component::Music>();
    CoreData::entityManager->registerComponent<Component::Sound>();
    /// SYSTEMS - CREATION
    CoreData::systemManager->createSystem<System::Render3DSystem>();
    CoreData::systemManager->createSystem<System::Render2DSystem>();
    CoreData::systemManager->createSystem<System::ClickEventSystem>();
    CoreData::systemManager->createSystem<System::KeyEventSystem>();
    CoreData::systemManager->createSystem<System::MouseEventSystem>();
    CoreData::systemManager->createSystem<System::ClickFocusSystem>();
    CoreData::systemManager->createSystem<Engine::TimerSystem>(*CoreData::entityManager);
    CoreData::systemManager->createSystem<Engine::PhysicsSystem>(*CoreData::entityManager);
    CoreData::systemManager->createSystem<System::HitboxSystem>();
    CoreData::systemManager->createSystem<System::MusicSystem>();
    CoreData::systemManager->createSystem<System::SoundSystem>();
    // SCENES - CREATION
    CoreData::sceneManager->createScene<DebugScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<MainMenuScene>((*CoreData::systemManager));
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
