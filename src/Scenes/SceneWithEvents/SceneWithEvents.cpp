/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 SceneWithEvents.cpp.cc
*/

#include "SceneWithEvents.hpp"

using namespace Game;

void SceneWithEvents::eventDispatcher(Engine::SystemManager &systemManager)
{
    auto clickEventSystem = systemManager.getSystem<System::ClickEventSystem>();
    auto keyEventSystem = systemManager.getSystem<System::KeyEventSystem>();
    auto mouseMoveEventSystem = systemManager.getSystem<System::MouseEventSystem>();

    if (Game::CoreData::eventManager->isMouseLeftPressed() || Game::CoreData::eventManager->isMouseRightPressed()
        || Game::CoreData::eventManager->isMouseMiddlePressed()) {
        clickEventSystem.update();
    }
    if (Game::CoreData::eventManager->isMouseMoved()) {
        mouseMoveEventSystem.update();
    }
    keyEventSystem.update();
}
