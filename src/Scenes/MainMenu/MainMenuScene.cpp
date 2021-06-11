/*
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

static const std::vector<raylib::MyVector2> buttonPosition = {
    raylib::MyVector2(340, 325),
    raylib::MyVector2(340, 400),
    raylib::MyVector2(340, 505),
    raylib::MyVector2(650, 505),
};

void MainMenuScene::open()
{
    auto scene = CoreData::sceneManager->getCurrentScene();
    const GUI::ButtonConfig largeButton = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(600, 55));
    const GUI::ButtonConfig mediumButton = GUI::ButtonFactory::getStandardButtonConfig(raylib::MyVector2(290, 55));
    const raylib::MyVector2 windowSize(CoreData::settings->getMyVector2("WIN_SIZE"));

    // GAME TITLE //340
    GUI::ImageFactory::create(scene->localEntities,
        raylib::MyVector2((windowSize.a / 2) - (592 / 2), 50),
        raylib::MyVector2(-1, -1),
        "./Asset/Interface/TitleLogo.png");
    // BUTTON
    GUI::ButtonFactory::create(scene->localEntities, buttonPosition[0], "play", largeButton, "Play", [](const Engine::Entity) {
        std::cout << "Play" << std::endl;
    });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[1], "credit", largeButton, "Credit", [](const Engine::Entity) {
            std::cout << "Go to credit" << std::endl;
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[2], "options", mediumButton, "Options", [](const Engine::Entity) {
            CoreData::sceneManager->setScene<OptionsMenuScene>();
        });
    GUI::ButtonFactory::create(
        scene->localEntities, buttonPosition[3], "quit", mediumButton, "Quit Game", [](const Engine::Entity) {
            CoreData::_window->close();
            // CoreData::_window->close();
        });
}

void Game::MainMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}