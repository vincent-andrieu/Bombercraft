/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.cpp.cc
*/

#include "Core.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Scenes/SkinChoice/SkinChoiceScene.hpp"
#include "Scenes/SoundOption/SoundOptionScene.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Scenes/CreditScene/CreditScene.hpp"
#include "Scenes/RessourcePackMenu/RessourcePackMenuScene.hpp"
#include "Components/Chrono/Chrono.hpp"
#include "Components/Sound/Sound.hpp"
#include "Components/Option/OptionComponent.hpp"
#include "Components/StringChoice/StringChoice.hpp"
#include "Systems/Audio/AudioSystem.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "Game/Factories/Sound/AudioFactory.hpp"

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
    CoreData::entityManager->registerComponent<Component::StringChoice>();
    CoreData::entityManager->registerComponent<Component::PlayerConfig>();
    CoreData::entityManager->registerComponent<Engine::Velocity>();
    CoreData::entityManager->registerComponent<Engine::Timer>();
    CoreData::entityManager->registerComponent<Engine::Script>();
    CoreData::entityManager->registerComponent<Component::Chrono>();
    CoreData::entityManager->registerComponent<Component::TextInputConfig>();
    CoreData::entityManager->registerComponent<Component::Sound>();
    CoreData::entityManager->registerComponent<Component::OptionComponent>();
    CoreData::entityManager->registerComponent<Component::PlayerInventory>();
    /// COMPONENTS - CREATION
    Engine::Entity options = this->globalEntities.createEntity("options");
    CoreData::entityManager->addComponent<Component::OptionComponent>(
        options, CoreData::settings->getFloat("STANDARD_SOUND_VOLUME"), CoreData::settings->getString("STANDARD_RESSOURCE_PACK"));
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
    CoreData::sceneManager->createScene<DebugScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<MainMenuScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<SkinChoiceScene>();
    CoreData::sceneManager->createScene<SplashScreenScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<OptionsMenuScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<KeyBindingMenuScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<LoadingScreenScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<PauseMenuScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<GameScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<SoundOptionScene>();
    CoreData::sceneManager->createScene<NewGameMenuScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<EndGameScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<CreditScene>(*CoreData::systemManager);
    CoreData::sceneManager->createScene<RessourcePackMenuScene>(*CoreData::systemManager);
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
    // MUSIC
    this->loadMusic();
}

void Core::loop()
{
    const std::string iconPath = CoreData::settings->getString("STANDARD_ICON_FILEPATH");
    // DEBUG - END
    SceneLoader::setScene<MainMenuScene>();
    CoreData::systemManager->getSystem<System::AudioSystem>().play("MENU", this->globalEntities);
    CoreData::window->setExitKey();
    CoreData::window->setWindowIcon(iconPath);
    while (CoreData::window->isOpen() && this->_loop == true) {
        CoreData::window->clear();
        CoreData::sceneManager->run();
        CoreData::window->refresh();
        CoreData::sceneManager->updateScene();
        CoreData::systemManager->getSystem<System::AudioSystem>().update();
    }
}

void Core::loadMusic()
{
    std::unordered_map<std::string, std::string> listMusic = this->getMusicList();

    for (auto once : listMusic)
        Game::AudioFactory::create(this->globalEntities, Game::AudioType::MUSIC, once.second, once.first);
    listMusic.clear();
}

std::unordered_map<std::string, std::string> Core::getMusicList() const
{
    std::vector<std::string> listMusicPath = CoreData::settings->getTabString("MUSIC_FILE_LIST_PATH");
    std::vector<std::string> listMusicName = CoreData::settings->getTabString("MUSIC_FILE_LIST_NAME");
    std::unordered_map<std::string, std::string>::iterator it;
    std::unordered_map<std::string, std::string> listMusic;

    if (listMusicPath.size() != listMusicName.size())
        throw std::invalid_argument("MUSIC_FILE_LIST_PATH and MUSIC_FILE_LIST_NAME must have the same size");
    for (size_t i = 0; i < listMusicPath.size(); i++) {
        it = listMusic.find(listMusicName[i]);
        if (it != listMusic.end())
            throw std::invalid_argument("MUSIC_FILE_LIST_NAME : all member must be different");
        listMusic[listMusicName[i]] = listMusicPath[i];
    }
    return listMusic;
}