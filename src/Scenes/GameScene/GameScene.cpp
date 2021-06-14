/*
** EPITECH PROJECT, 2021
** Scenes
** File description:
** 03/06/2021 GameScene.cpp.cc
*/

#include "GameScene.hpp"

using namespace Game;

static const std::vector<std::string> texturesPath = {
    "./Asset/Interface/PowerUpBox.png",
    "./Asset/Interface/InventoryBomb.png",
    "./Asset/Interface/InventorySpeed.png",
    "./Asset/Interface/InventoryWallPass.png",
    "./Asset/Interface/InventoryBlastRadius.png",
};

static const std::vector<std::string> inventoryNames = {
    "GameInventory1",
    "GameInventory2",
    "GameInventory3",
    "GameInventory4",
};

GameScene::GameScene(Engine::SystemManager &systemManager) : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void GameScene::open()
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    const std::vector<raylib::MyVector2> inventoryPosition = {raylib::MyVector2(0, 0),
        raylib::MyVector2(windowSize.a - (windowSize.a / 15) * 4, 0),
        raylib::MyVector2(0, windowSize.b - (windowSize.a / 15)),
        raylib::MyVector2(windowSize.a - (windowSize.a / 15) * 4, windowSize.b - (windowSize.a / 15))};
    size_t nbPlayer = 3;

    auto background = this->localEntities.createEntity("GameBackground");
    CoreData::entityManager->addComponent<Component::Render2D>(background,
        Component::render2dMapModels({{"GameBackgroundRectangle",
            std::make_shared<raylib::Rectangle>(
                raylib::MyVector2(0, 0), raylib::MyVector2(windowSize.a, windowSize.b), raylib::RColor::RPURPLE)}}));
    for (size_t i = 0; i < nbPlayer; i++) {
        GUI::InventoryFactory::create(this->localEntities,
            inventoryPosition[i],
            {windowSize.a / 15, windowSize.a / 15},
            texturesPath,
            GUI::InventoryFactory::getStandardLabelConfig(),
            inventoryNames[i]);
    }
}

void GameScene::update()
{
    try {
        auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();
        auto &timer = this->_systemManager.getSystem<Engine::TimerSystem>();

        render2D.update();
        timer.update();
        this->eventDispatcher(this->_systemManager);
    } catch (std::invalid_argument const &e) {
        std::cerr << e.what() << std::endl;
        exit(84); // TEMPORARY
    }
}