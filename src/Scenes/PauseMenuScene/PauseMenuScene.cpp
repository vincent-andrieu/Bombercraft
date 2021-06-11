/*
** EPITECH PROJECT, 2021
** PauseMenuScene.cpp
** File description:
** Implementation of scene : pause menu, during a game
*/

#include "PauseMenuScene.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render2D/singleRender2DSystem.hpp"

Game::PauseMenuScene::PauseMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
}

void Game::PauseMenuScene::open()
{
    GUI::ButtonFactory::create(localEntities,
        {20, 20},
        "my_label",
        GUI::ButtonFactory::getStandardButtonConfig(),
        "button_text",
        [](const Engine::Entity entity) {
            std::cout << "Hello " << entity << std::endl;
        });
}

void Game::PauseMenuScene::update()
{
    auto &singleRender2D = this->_systemManager.getSystem<System::singleRender2DSystem>();
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    try {
        singleRender2D.update();
        render2D.update();
        this->eventDispatcher(this->_systemManager);
    } catch (std::invalid_argument const &e) {
        std::cerr << e.what() << std::endl;
        exit(84); // TEMPORARY
    }
}