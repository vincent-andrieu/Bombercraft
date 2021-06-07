/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 MainMenuScene.cpp.cc
*/

#include "MainMenuScene.hpp"

using namespace Game;

Game::MainMenuScene::MainMenuScene(Engine::SystemManager &systemManager) : Engine::AbstractScene(systemManager, *CoreData::entityManager),
      SceneWithEvents(*CoreData::eventManager)
{
    /// CREATE local Entities and Components
    //    Engine::Entity playButton = this->localEntities.createEntity("button_play");
    //    this->_entityManager.addComponent<Component::ClickEvent>(/* handler*/, /* trigger requirements */);
    //    this->_entityManager.addComponent<Component::Render2d>(/* raylib object */);
}

void Game::MainMenuScene::update()
{
    auto &render2D = this->_systemManager.getSystem<System::Render2DSystem>();

    render2D.update();
    this->eventDispatcher(_systemManager);
}
