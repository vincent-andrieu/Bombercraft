/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 SceneWithEvents.cpp.cc
*/

#include "SceneWithEvents.hpp"

using namespace Game;

SceneWithEvents::SceneWithEvents(raylib::Input &eventManager) : _eventManager(eventManager)
{
}

void SceneWithEvents::eventDispatcher(Engine::SystemManager &systemManager)
{
    auto clickEventSystem = systemManager.getSystem<System::ClickEventSystem>();
    auto keyEventSystem = systemManager.getSystem<System::KeyEventSystem>();
    auto mouseMoveEventSystem = systemManager.getSystem<System::MouseEventSystem>();

    if (_eventManager.isMouseLeftPressed() || _eventManager.isMouseRightPressed() || _eventManager.isMouseMiddlePressed()) {
        clickEventSystem.update();
    }
    if (_eventManager.isMouseMoved()) {
        mouseMoveEventSystem.update();
    }
    keyEventSystem.update();
}
