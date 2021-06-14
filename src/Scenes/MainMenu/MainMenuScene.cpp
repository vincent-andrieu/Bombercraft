/*50
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 MainMenuScene.cpp.cc
*/

#include "MainMenuScene.hpp"

using namespace Game;

MainMenuScene::MainMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void MainMenuScene::open()
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    static const auto &windowSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));

    ProportionUtilities my_utility(windowSize);
    const std::vector<raylib::MyVector2> buttonPosition = {my_utility.getProportion({25, 40}),
        my_utility.getProportion({25, 50}),
        my_utility.getProportion({25, 65}),
        my_utility.getProportion({50.5, 65})};
    const GUI::ButtonConfig largeButton(GUI::ButtonFactory::getLargeButtonConfig());
    const GUI::ButtonConfig mediumButton(GUI::ButtonFactory::getMediumButtonConfig());

    raylib::MyVector2 logoSize(my_utility.getProportion({70, 25}));
    // GAME TITLE //340
    GUI::ImageFactory::create(scene->localEntities,
        my_utility.getProportion({50, 20}, logoSize, {50, 50}),
        logoSize,
        Game::CoreData::settings->getString("BOMBERCRAFT_LOGO"),
        true);
    // BUTTON
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[0], "play", largeButton, "Play", [](const Engine::Entity) {
        std::cout << "Play" << std::endl;
    });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[1], "credit", largeButton, "Credit", [](const Engine::Entity) {
            std::cout << "Go to credit" << std::endl;
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[2], "options", mediumButton, "Options...", [](const Engine::Entity) {
            CoreData::sceneManager->setScene<OptionsMenuScene>();
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[3], "quit", mediumButton, "Quit Game", [](const Engine::Entity) {
            // CoreData::_window->close();
        });
}

void Game::MainMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}