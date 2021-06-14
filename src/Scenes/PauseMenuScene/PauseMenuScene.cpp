/*
** EPITECH PROJECT, 2021
** PauseMenuScene.cpp
** File description:
** Implementation of scene : pause menu, during a game
*/

#include "PauseMenuScene.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"

Game::PauseMenuScene::PauseMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void Game::PauseMenuScene::open()
{
    ProportionUtilities my_utility(CoreData::settings->getMyVector2("WIN_SIZE"));
    auto my_buttonConfig(GUI::ButtonFactory::getLargeButtonConfig());
    const std::string my_buttonNamePrefix("button_");

    GUI::LabelFactory::createCentered(localEntities,
        my_utility.getProportion(raylib::MyVector2(50, 20)),
        "Game Menu",
        GUI::LabelFactory::getStandardLabelConfig(CoreData::settings->getInt("STANDARD_FONT_SIZE")));

    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({50, 40}, my_buttonConfig.size),
        my_buttonNamePrefix + "continue",
        my_buttonConfig,
        "Back to Game",
        [](const Engine::Entity) {
            CoreData::sceneManager->setScene<Game::GameScene>();
        });
    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({50, 60}, my_buttonConfig.size),
        my_buttonNamePrefix + "options",
        my_buttonConfig,
        "Options...",
        [](const Engine::Entity) {
            CoreData::sceneManager->setScene<Game::OptionsMenuScene>();
        });
    GUI::ButtonFactory::create(localEntities,
        my_utility.getProportion({50, 70}, my_buttonConfig.size),
        my_buttonNamePrefix + "quit",
        my_buttonConfig,
        "Save and quit to title",
        [](const Engine::Entity) {
            CoreData::sceneManager->setScene<Game::MainMenuScene>();
        });
}

void Game::PauseMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    try {
        render2D.update();
        this->eventDispatcher(this->_systemManager);
    } catch (std::invalid_argument const &e) {
        std::cerr << e.what() << std::endl;
        exit(84); // TEMPORARY
    }
}