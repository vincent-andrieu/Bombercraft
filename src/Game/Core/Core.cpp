/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Scenes/SoundOption/SoundOptionScene.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Components/Chrono/Chrono.hpp"
#include "Components/Sound/Sound.hpp"
#include "Components/Option/OptionComponent.hpp"
#include "Systems/Audio/AudioSystem.hpp"
#include "Game/Factories/Map/Component/Matrix2D.hpp"

using namespace Game;

Core::Core() : CoreData(), globalEntities(*CoreData::entityManager)
{
    /// COMPONENTS - DEFINITION
    CoreData::entityManager->registerComponent<Component::Matrix2D>();
    CoreData::entityManager->registerComponent<Component::Render2D>();
    CoreData::entityManager->registerComponent<Component::Render3D>();
    CoreData::entityManager->registerComponent<Component::ClickEvent>();
    CoreData::entityManager->registerComponent<Component::ClickFocusEvent>();
    CoreData::entityManager->registerComponent<Component::KeyEvent>();
    CoreData::entityManager->registerComponent<Component::MouseMoveEvent>();
    CoreData::entityManager->registerComponent<Component::Hitbox>();
    CoreData::entityManager->registerComponent<Engine::Position>();
    CoreData::entityManager->registerComponent<Component::KeyBox>();
    CoreData::entityManager->registerComponent<Component::PlayerConfig>();
    // Component::
    CoreData::entityManager->registerComponent<Engine::Velocity>();
    CoreData::entityManager->registerComponent<Engine::Timer>();
    CoreData::entityManager->registerComponent<Engine::Script>();
    CoreData::entityManager->registerComponent<Component::Chrono>();
    CoreData::entityManager->registerComponent<Component::TextInputConfig>();
    CoreData::entityManager->registerComponent<Component::Sound>();
    CoreData::entityManager->registerComponent<Component::OptionComponent>();
    /// COMPONENTS - CREATION
    Engine::Entity options = this->globalEntities.createEntity("options");
    CoreData::entityManager->addComponent<Component::OptionComponent>(options, CoreData::settings->getFloat("DEF_SOUND_VOLUME"));
    /// SYSTEMS - CREATION
    CoreData::systemManager->createSystem<System::Render3DSystem>();
    CoreData::systemManager->createSystem<System::Render2DSystem>();
    CoreData::systemManager->createSystem<System::ClickEventSystem>();
    CoreData::systemManager->createSystem<System::KeyEventSystem>();
    CoreData::systemManager->createSystem<System::MouseEventSystem>();
    CoreData::systemManager->createSystem<System::ClickFocusSystem>();
    CoreData::systemManager->createSystem<Engine::TimerSystem>(*CoreData::entityManager);
    CoreData::systemManager->createSystem<System::PhysicsSystem>();
    CoreData::systemManager->createSystem<System::HitboxSystem>();
    CoreData::systemManager->createSystem<System::AudioSystem>();
    CoreData::systemManager->createSystem<System::PlayerConfigSystem>();
    /// SCENES - CREATION
    CoreData::sceneManager->createScene<DebugScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<MainMenuScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<SplashScreenScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<OptionsMenuScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<KeyBindingMenuScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<LoadingScreenScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<PauseMenuScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<GameScene>((*CoreData::systemManager));
    CoreData::sceneManager->createScene<SoundOptionScene>();
    // DEBUG - START - Remove when players with PlayerConfig Component will be added
    auto entity = CoreData::entityManager->createEntity();
    CoreData::entityManager->addComponent<Component::PlayerConfig>(entity,
        Component::PlayerID::ALPHA,
        Component::PlayerKeyBindings{
            raylib::KeyBoard::IKEY_UP,
            raylib::KeyBoard::IKEY_DOWN,
            raylib::KeyBoard::IKEY_LEFT,
            raylib::KeyBoard::IKEY_RIGHT,
            raylib::KeyBoard::IKEY_END,
            raylib::KeyBoard::IKEY_R_SHIFT,
        });
    CoreData::systemManager->getSystem<System::PlayerConfigSystem>().addEntity(entity);

    entity = CoreData::entityManager->createEntity();
    CoreData::entityManager->addComponent<Component::PlayerConfig>(entity,
        Component::PlayerID::BRAVO,
        Component::PlayerKeyBindings{
            raylib::KeyBoard::IKEY_Z,
            raylib::KeyBoard::IKEY_S,
            raylib::KeyBoard::IKEY_Q,
            raylib::KeyBoard::IKEY_D,
            raylib::KeyBoard::IKEY_W,
            raylib::KeyBoard::IKEY_L_ALT,
        });
    CoreData::systemManager->getSystem<System::PlayerConfigSystem>().addEntity(entity);
    // DEBUG - END
    SceneLoader::setScene<MainMenuScene>();
}

void Core::loop()
{
    while (CoreData::_window->isOpen() && this->_loop == true) {
        CoreData::_window->clear();
        CoreData::sceneManager->run();
        CoreData::_window->refresh();
        CoreData::sceneManager->updateScene();
    }
}