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
#include "../../Game/CoreData/CoreData.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"

using namespace Game;

extern std::unique_ptr<Game::Core> core;

static const std::vector<std::string> inventoryNames = {
    "GameInventory1",
    "GameInventory2",
    "GameInventory3",
    "GameInventory4",
};

static void handlerGameTimeout()
{
    std::cout << "TIMEOUT - GAME OVER\n";
    CoreData::window->takeScreenshot("Asset/ScreenShot/GameShot.png");
    CoreData::sceneManager->setScene<EndGameScene>();
}

GameScene::GameScene(Engine::SystemManager &systemManager) : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void GameScene::open()
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    const std::vector<std::string> texturesPath = CoreData::settings->getTabString("INVENTORY_TEXTURE");
    const std::vector<raylib::MyVector2> inventoryPosition = {raylib::MyVector2(0, 0),
        raylib::MyVector2(windowSize.a - (windowSize.a / 15) * 4, 0),
        raylib::MyVector2(0, windowSize.b - (windowSize.a / 15)),
        raylib::MyVector2(windowSize.a - (windowSize.a / 15) * 4, windowSize.b - (windowSize.a / 15))};
    const std::vector<Component::PlayerID> ids = {
        Component::PlayerID::ALPHA, Component::PlayerID::BRAVO, Component::PlayerID::CHARLIE, Component::PlayerID::DELTA};
    size_t nbPlayer = 3;
    ProportionUtilities proportion(windowSize);

    /// Inventory
    for (size_t i = 0; i < nbPlayer; i++) {
        GUI::InventoryFactory::create(this->localEntities,
            inventoryPosition[i],
            {windowSize.a / 15, windowSize.a / 15},
            texturesPath,
            GUI::LabelFactory::getStandardLabelConfig(20),
            ids[i],
            inventoryNames[i]);
    }
    /// Chrono
    raylib::MyVector2 countdownSize = CoreData::settings->getMyVector2("TIMER_SIZE");
    GUI::CountdownFactory::create(this->localEntities,
        proportion.getProportion({50, 0}, {countdownSize.a, 0}),
        CoreData::settings->getInt("STANDARD_COUNTDOWN"),
        handlerGameTimeout);
    /// MAP
    GUI::MapFactory::create(this->localEntities, "gameMap");
    /// Camera
    // Temporary, replace by : CoreData::setCamera..(position, target)
    CoreData::camera->setPosition(CoreData::settings->getMyVector3("CAM_POSITION"));
    CoreData::camera->setTarget(CoreData::settings->getMyVector3("CAM_TARGET"));
    CoreData::camera->setUp(CoreData::settings->getMyVector3("CAM_UP"));
    CoreData::systemManager->getSystem<System::AudioSystem>().play("GAME", core->globalEntities);

    std::unordered_map<raylib::KeyBoard, Component::eventScript> my_keyTriggers;
    my_keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, [](Engine::Entity) {
        CoreData::sceneManager->pushLastScene();
        CoreData::sceneManager->setScene<PauseMenuScene>();
    }));
    Game::KeyManagementFactory::create(localEntities, my_keyTriggers);
}

void GameScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
    auto &render3D = this->_systemManager.getSystem<System::Render3DSystem>();
    auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

    render3D.update();
    render2D.update();
    timer.update();
    this->eventDispatcher(this->_systemManager);
}