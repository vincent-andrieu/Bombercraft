/*
** EPITECH PROJECT, 2021
** NewGameMenuScene.cpp
** File description:
** Implementation of scene to display previous games before choosing or creating one to play
*/

#include "NewGameMenuScene.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Scenes/GameScene/GameScene.hpp"

static const string my_button_prefix("button_");

Game::NewGameMenuScene::NewGameMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void Game::NewGameMenuScene::init()
{
    const auto &windowSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));
    ProportionUtilities my_utility(windowSize);
    GUI::ButtonConfig my_smallButtonConfig(GUI::ButtonFactory::getSmallButtonConfig());
    GUI::ButtonConfig my_mediumButtonConfig(GUI::ButtonFactory::getMediumButtonConfig());

    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion(67, 85),
        my_button_prefix + "cancel",
        my_smallButtonConfig,
        "Cancel",
        [](const Engine::Entity) {
            CoreData::sceneManager->setScene(CoreData::sceneManager->peekLastScene());
        });

    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({55.5, 75}),
        my_button_prefix + "newGame",
        my_mediumButtonConfig,
        "Create New Game",
        [](const Engine::Entity) {
            CoreData::sceneManager->setScene<GameScene>();
        });
}

void Game::NewGameMenuScene::open()
{
    init();
}

void Game::NewGameMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}