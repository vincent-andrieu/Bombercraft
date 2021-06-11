/*50
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 MainMenuScene.cpp.cc
*/

#include "MainMenuScene.hpp"

using namespace Game;

Game::MainMenuScene::MainMenuScene(Engine::SystemManager &systemManager)
    : Engine::AbstractScene(systemManager, *CoreData::entityManager)
{
}

void MainMenuScene::open()
{
    /// Call factories Here
}

void Game::MainMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(this->_systemManager);
}