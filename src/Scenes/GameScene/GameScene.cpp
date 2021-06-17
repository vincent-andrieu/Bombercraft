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
#include "Game/Factories/Bomb/BombFactory.hpp"
#include "Game/Factories/Character/CharacterFactory.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Systems/ModelList/ModelListSystem.hpp"
#include "Systems/PhysicsSystem/PhysicsSystem.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "Components/Option/OptionComponent.hpp"
#include "Game/Factories/Character/AIComponent/AIComponent.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

const std::unordered_map<Component::PlayerID, std::string> Game::PLAYER_ID_TO_NAME({
    {Component::ALPHA, "TL_ALPHA"},
    {Component::BRAVO, "TR_BRAVO"},
    {Component::DELTA, "BL_DELTA"},
    {Component::CHARLIE, "BR_CHARLIE"},
});

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
    GUI::MapFactory::create(this->localEntities, ressourcePackRoot, "gameMap");
    /// Camera
    CoreData::moveCamera(CoreData::settings->getMyVector3("CAM_POSITION"), CoreData::settings->getMyVector3("CAM_TARGET"));
    CoreData::camera->setUp(CoreData::settings->getMyVector3("CAM_UP"));
    CoreData::systemManager->getSystem<System::AudioSystem>().play("GAME", core->globalEntities);
    /// CHARACTERS
    this->createCharacters();
    /// PAUSE SHORTCUT
    std::unordered_map<raylib::KeyBoard, Component::eventScript> my_keyTriggers;
    my_keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, [this](Engine::Entity) {
        this->_systemManager.getSystem<Engine::TimerSystem>().pause();
        CoreData::window->takeScreenshot("Asset/ScreenShot/GameShot.png");
        Game::CoreData::camera->setFovy((float) CoreData::settings->getInt("STANDARD_CAMERA_FOV"));
        CoreData::sceneManager->pushLastScene();
        CoreData::sceneManager->setScene<PauseMenuScene>(false);
    }));
    Game::KeyManagementFactory::create(localEntities, my_keyTriggers);
}

void GameScene::createCharacters()
{
    Engine::Entity optionEntity = core->globalEntities.getEntity("options");
    auto &options = CoreData::entityManager->getComponent<Component::OptionComponent>(optionEntity);
    auto &map = CoreData::entityManager->getComponent<Component::Matrix2D>(this->localEntities.getEntity("gameMap"));
    Engine::Entity entity;
    Component::AIComponent AI;

    Component::PlayerConfig *config[4] = {
        &CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config1")),
        &CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config2")),
        &CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config3")),
        &CoreData::entityManager->getComponent<Component::PlayerConfig>(core->globalEntities.getEntity("config4"))};
    for (size_t i = 0; i < 4; i++) {
        entity = CharacterFactory::create(this->localEntities, *config[i], map, (i >= options.nbPlayers));
        if (i >= options.nbPlayers) {
            AI = Game::CoreData::entityManager->getComponent<Component::AIComponent>(entity);
            AI.setRandomness(options.IARandomProb);
        }
    }
}

uint GameScene::getNbrPlayers()
{
    uint counter = 0;

    for (const auto &player : Game::PLAYER_ID_TO_NAME)
        if (CoreData::sceneManager->getCurrentScene()->localEntities.entityIsSet(player.second))
            counter++;
    return counter;
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

    double calculationPerSecond((double) CoreData::settings->getInt("CPS"));
    double frames(0);

    core->_clock.setElapsedTime();
    frames = core->_clock.getElapsedTimeDouble() * calculationPerSecond;
    if (frames != 0) {
        core->_clock.resetStartingPoint();
        while (frames-- > 0) {
            render3D.update();
            render2D.update();
            modelList.update();
            hitbox.update();
            physic.update(dt);
            this->eventDispatcher(this->_systemManager);
        }
    }
    audio.update();
    timer.update();
}