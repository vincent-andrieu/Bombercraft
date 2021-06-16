/*
** EPITECH PROJECT, 2021
** Scenes
** File description:
** 03/06/2021 GameScene.cpp.cc
*/

#include "GameScene.hpp"
#include "GUI/Factories/Countdown/CountdownFactory.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Game/Factories/Map/MapFactory.hpp"
#include "Game/Factories/Character/CharacterFactory.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Systems/ModelList/ModelListSystem.hpp"
#include "Systems/PhysicsSystem/PhysicsSystem.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "Components/Option/OptionComponent.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

static void handlerGameTimeout()
{
    Game::CoreData::camera->setFovy((float) CoreData::settings->getInt("STANDARD_CAMERA_FOV"));
    CoreData::window->takeScreenshot("Asset/ScreenShot/GameShot.png");
    CoreData::sceneManager->setScene<EndGameScene>();
}

GameScene::GameScene(Engine::SystemManager &systemManager) : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void GameScene::open()
{
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = Game::CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities proportion(windowSize);

    /// Chrono
    const raylib::MyVector2 &countdownSize = CoreData::settings->getMyVector2("TIMER_SIZE");
    GUI::CountdownFactory::create(this->localEntities,
        proportion.getProportion({50, 0}, {countdownSize.a, 0}),
        options.gameTimerDuration,
        handlerGameTimeout);
    /// OPTIONS
    /// MAP
    const string &ressourcePackRoot = options.ressourcePack;
    std::cout << "Ressource pack: " << ressourcePackRoot << std::endl;
    GUI::MapFactory::create(this->localEntities, ressourcePackRoot, "gameMap");
    GUI::BlockFactory::create(this->localEntities, raylib::MyVector3(1 * 2, 0, 11 * 2), GUI::BlockFactory::BlockType::BLOCK_BOMB, ressourcePackRoot);
    /// Camera
    CoreData::moveCamera(CoreData::settings->getMyVector3("CAM_POSITION"), CoreData::settings->getMyVector3("CAM_TARGET"));
    CoreData::camera->setUp(CoreData::settings->getMyVector3("CAM_UP"));
    CoreData::systemManager->getSystem<System::AudioSystem>().play("GAME", core->globalEntities);
    /// CHARACTERS
    auto &config = CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config1"));
    auto &map = CoreData::entityManager->getComponent<Component::Matrix2D>(this->localEntities.getEntity("gameMap"));
    CharacterFactory::create(this->localEntities, config, map, false);
    /// PAUSE SHORTCUT
    std::unordered_map<raylib::KeyBoard, Component::eventScript> my_keyTriggers;
    my_keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, [](Engine::Entity) {
        CoreData::window->takeScreenshot("Asset/ScreenShot/GameShot.png");
        Game::CoreData::camera->setFovy((float) CoreData::settings->getInt("STANDARD_CAMERA_FOV"));
        CoreData::sceneManager->pushLastScene();
        CoreData::sceneManager->setScene<PauseMenuScene>(false);
    }));
    Game::KeyManagementFactory::create(localEntities, my_keyTriggers);
}

void GameScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto &render3D = this->_systemManager.getSystem<System::Render3DSystem>();
    auto &modelList = this->_systemManager.getSystem<System::ModelListSystem>();
    auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();
    auto &audio = this->_systemManager.getSystem<System::AudioSystem>();
    auto &physic = this->_systemManager.getSystem<System::PhysicsSystem>();
    auto &hitbox = this->_systemManager.getSystem<System::HitboxSystem>();
    float dt = 1.0f / 10.0f;

    render3D.update();
    modelList.update();
    render2D.update();
    timer.update();
    audio.update();
    hitbox.update();
    physic.update(dt);
    this->eventDispatcher(this->_systemManager);
}