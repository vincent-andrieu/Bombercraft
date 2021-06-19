/*
 * EPITECH PROJECT, 2021
 * SaveMenu
 * File description:
 * SaveMenuScene.cpp - Created: 19/06/2021
 */

#include "SaveMenuScene.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Scenes/NewGameMenuScene/NewGameMenuScene.hpp"
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"
#include "Game/Factories/KeyManagementFactory/KeyManagementFactory.hpp"

using namespace raylib;

static const Component::eventScript cancelButtonHandler = [](const Engine::Entity &) {
    Game::CoreData::sceneManager->setScene(Game::CoreData::sceneManager->peekLastScene());
};

static const Component::eventScript newGameButtonHandler = [](const Engine::Entity &) {
    Game::CoreData::sceneManager->pushLastScene();
    Game::CoreData::sceneManager->setScene<Game::NewGameMenuScene>();
};

Game::SaveMenuScene::SaveMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void Game::SaveMenuScene::open()
{
    const MyVector2 &window_size = CoreData::settings->getMyVector2("WIN_SIZE");
    const ProportionUtilities resizer(window_size);
    GUI::ButtonConfig menuButtons = GUI::ButtonFactory::getMediumButtonConfig();

    GUI::ImageFactory::create(
        this->localEntities, MyVector2(0, 0), window_size, CoreData::settings->getString("STANDARD_BACKGROUND"), false);
    GUI::LabelFactory::createCentered(this->localEntities, resizer(50, 4), "Saves", GUI::LabelFactory::getStandardLabelConfig());

    GUI::ButtonFactory::create(
        this->localEntities, resizer(25, 90), "cancelButton", menuButtons, "Cancel", cancelButtonHandler, true);
    GUI::ButtonFactory::create(
        this->localEntities, resizer(75, 90), "newGame", menuButtons, "New Game", newGameButtonHandler, true);

    // KEYS
    std::unordered_map<raylib::KeyBoard, Component::eventScript> keyTriggers;
    keyTriggers.emplace(std::make_pair(raylib::KeyBoard::IKEY_ESCAPE, cancelButtonHandler));
    Game::KeyManagementFactory::create(this->localEntities, keyTriggers);
}

void Game::SaveMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}