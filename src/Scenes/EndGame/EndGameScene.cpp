/*
** EPITECH PROJECT, 2021
** Scenes
** File description:
** 03/06/2021 EndGameScene.cpp.cc
*/

#include "EndGameScene.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "GUI/Factories/Checkbox/CheckboxFactory.hpp"
#include "GUI/Factories/Countdown/CountdownFactory.hpp"
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "GUI/Factories/Image/ImageSequenceFactory.hpp"

using namespace Game;

EndGameScene::EndGameScene(Engine::SystemManager &systemManager) : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

static void goToGameScene(const Engine::Entity)
{
    Game::CoreData::sceneManager->setScene<Game::GameScene>();
}

static void goToMainMenuScene(const Engine::Entity)
{
    Game::CoreData::sceneManager->setScene<Game::MainMenuScene>();
}

void EndGameScene::open()
{
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities myUtility(CoreData::settings->getMyVector2("WIN_SIZE"));
    auto myButtonConfig(GUI::ButtonFactory::getMediumButtonConfig());

    // BACKGROUND
    GUI::ImageFactory::create(
        this->localEntities, raylib::MyVector2(0, 0), windowSize, CoreData::settings->getString("GAME_SCREENSHOT"), false);
    auto background = this->localEntities.createEntity("EndGameBackground");
    CoreData::entityManager->addComponent<Component::Render2D>(background,
        Component::render2dMapModels({{"EndGameBackgroundRectangle",
            std::make_shared<raylib::Rectangle>(raylib::MyVector2(0, 0), windowSize, raylib::RColor::RSHADOW)}}));

    // BUTTONS
    GUI::ButtonFactory::create(localEntities,
        myUtility.getProportion({30, 90}, myButtonConfig.size),
        "EndGameRestartButton",
        myButtonConfig,
        "Restart",
        goToGameScene);
    GUI::ButtonFactory::create(localEntities,
        myUtility.getProportion({70, 90}, myButtonConfig.size),
        "EndGameMainMenuButton",
        myButtonConfig,
        "Main Menu",
        goToMainMenuScene);

    // TEXT
    GUI::LabelFactory::createCentered(localEntities,
        myUtility.getProportion(raylib::MyVector2(50, 10)),
        "End Of Game",
        GUI::LabelFactory::getStandardLabelConfig(CoreData::settings->getInt("STANDARD_FONT_SIZE")));

    // MODEL
}

void EndGameScene::update()
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