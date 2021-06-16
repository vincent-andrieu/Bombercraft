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
#include "Components/ModelList/ModelList.hpp"
#include "Components/StringChoice/StringChoice.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"

#include "Systems/Audio/AudioSystem.hpp"
#include "Systems/ModelList/ModelListSystem.hpp"

#include "Game/Factories/Sound/AudioFactory.hpp"

using namespace Game;

const Texture2D &loadTexture(const std::string &toLoad)
{
    if (!raylib::Texture::_loaderManager)
        raylib::Texture::_loaderManager = std::make_shared<raylib::LoaderManager<Texture2D, std::string>>(
            raylib::Texture::myTextureLoad, raylib::Texture::myTextureUnload);
    return raylib::Texture::_loaderManager->load(toLoad);
}

const RModel &loadModel(const std::tuple<std::string, std::string> &toLoad)
{
    if (!raylib::Model::_loaderManager)
        raylib::Model::_loaderManager =
            std::make_shared<raylib::LoaderManager<RModel, std::tuple<std::string, std::string>, tuple_hash>>(
                raylib::Model::myModelLoad, raylib::Model::myModelUnload);
    return raylib::Model::_loaderManager->load(toLoad);
}

void Core::registerComponents()
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
    CoreData::entityManager->registerComponent<Component::ModelList>();
}

void Core::createSystems()
{
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
    CoreData::systemManager->createSystem<System::ModelListSystem>();
}

void Core::createScenes()
{
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
}

Core::Core()
    : CoreData(), globalEntities(*CoreData::entityManager), _preloadStatus(false),
      _preloadTexture(loadTexture,
          {
              "Asset/Interface/Button.png",
              "Asset/Interface/HoverButton.png",
              "Asset/Interface/Button.png",
              "Asset/Interface/UnavailableButton.png",
          }),
      _preloadModel(loadModel, {{}})
{
    this->registerComponents();
    /// COMPONENTS - CREATION
    Engine::Entity options = this->globalEntities.createEntity("options");
    CoreData::entityManager->addComponent<Component::OptionComponent>(options,
        CoreData::settings->getFloat("STANDARD_SOUND_VOLUME"),
        CoreData::settings->getString("STANDARD_RESSOURCE_PACK"),
        (size_t) CoreData::settings->getInt("STANDARD_CAMERA_FOV"));
    this->createSystems();
    this->createScenes();
    // DEBUG - START - Remove when players with PlayerConfig Component will be added
    auto entity = this->globalEntities.createEntity("config1");
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

    entity = this->globalEntities.createEntity("config2");
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
    // MUSIC
    // this->loadMusic();
}

void Core::_audioSystemUpdate()
{
    while (CoreData::window->isOpen() && this->_loop == true) {
        CoreData::systemManager->getSystem<System::AudioSystem>().update();
    }
}

void Core::loop()
{
    const std::string iconPath = CoreData::settings->getString("STANDARD_ICON_FILEPATH");

    CoreData::window->setExitKey();
    CoreData::window->setWindowIcon(iconPath);
    std::thread audioThread(&Core::_audioSystemUpdate, this);
    while (CoreData::window->isOpen() && this->_loop == true) {
        CoreData::window->clear();
        if (!this->isEndPreload()) {
            this->runPreload();
            this->printDuringPreload();
        } else {
            CoreData::sceneManager->run();
        }
        CoreData::window->refresh();
        CoreData::sceneManager->updateScene();
    }
    if (audioThread.joinable())
        audioThread.join();
}

void Core::loadMusic()
{
    std::unordered_map<std::string, std::string> listMusic = this->getAudioList("MUSIC_FILE_LIST_PATH", "MUSIC_FILE_LIST_NAME");
    std::unordered_map<std::string, std::string> listSound = this->getAudioList("SOUND_FILE_LIST_PATH", "SOUND_FILE_LIST_NAME");

    for (auto once : listMusic)
        Game::AudioFactory::create(this->globalEntities, Game::AudioType::MUSIC, once.second, once.first);
    for (auto once : listSound)
        Game::AudioFactory::create(this->globalEntities, Game::AudioType::SOUND, once.second, once.first);
}

std::unordered_map<std::string, std::string> Core::getAudioList(
    std::string const &varPathList, std::string const &varNameList) const
{
    std::vector<std::string> listAudioPath = CoreData::settings->getTabString(varPathList);
    std::vector<std::string> listAudioName = CoreData::settings->getTabString(varNameList);
    std::unordered_map<std::string, std::string>::iterator it;
    std::unordered_map<std::string, std::string> listAudio;

    if (listAudioPath.size() != listAudioName.size())
        throw std::invalid_argument("Core::getAudioList List name and path must have the same size");
    for (size_t i = 0; i < listAudioPath.size(); i++) {
        it = listAudio.find(listAudioName[i]);
        if (it != listAudio.end())
            throw std::invalid_argument("Core::getAudioList : members must be different");
        listAudio[listAudioName[i]] = listAudioPath[i];
    }
    return listAudio;
}

bool Core::isEndPreload()
{
    if (this->_preloadStatus)
        return true;
    if (this->_preloadModel.isFinish() && this->_preloadTexture.isFinish()) {
        this->_preloadStatus = true;
        this->loadMusic();
        this->runAfterPreload();
    }
    return false;
}

void Core::runPreload()
{
    if (!this->_preloadModel.isFinish())
        this->_preloadModel.nextLoad();
    else if (!this->_preloadTexture.isFinish())
        this->_preloadTexture.nextLoad();
}

void Core::runAfterPreload()
{
    SceneLoader::setScene<MainMenuScene>();
    CoreData::systemManager->getSystem<System::AudioSystem>().play("MENU", this->globalEntities);
}

void Core::printDuringPreload()
{
    size_t value = (this->_preloadTexture.getPourcentOfRun() / 2) + (this->_preloadModel.getPourcentOfRun() / 2);

    std::cout << "loading: " << value << "%" << std::endl;
}