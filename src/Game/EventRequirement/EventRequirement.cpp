/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventRequirement.cpp.cc
*/

#include "EventRequirement.hpp"

Game::EventRequirement::EventRequirement(clickType const click, bool mouseMove,
     std::vector<raylib::KeyBoard> const &keyPress,
     std::vector<raylib::KeyBoard> const &keyRelease)
    : _click(click), _mouseMoveEvent(mouseMove),
        _handledKeyPress(keyPress), _handledKeyRelease(keyRelease)
{
}

bool Game::EventRequirement::triggerClick(raylib::Input &eventManager) const
{
    if ((_click & (int)evtMouse::LEFT) && eventManager.isMouseLeftPressed()) {
        return true;
    }
    if ((_click & (int)evtMouse::RIGHT) && eventManager.isMouseRightPressed()) {
        return true;
    }
    if ((_click & (int)evtMouse::MIDDLE) && eventManager.isMouseMiddlePressed()) {
        return true;
    }
    return false;
}

bool Game::EventRequirement::triggerKey(raylib::Input &eventManager) const
{
    for (const auto &key : _handledKeyRelease) {
        if (eventManager.isKeyReleased(key)) {
            return true;
        }
    }
    for (const auto &key : _handledKeyPress) {
        if (eventManager.isKeyPressed(key)) {
            return true;
        }
    }
    return false;
}

bool Game::EventRequirement::triggerMouseMove(raylib::Input &eventManager) const
{
    return _mouseMoveEvent;
}

bool Game::EventRequirement::isTrigger(raylib::Input &eventManager)
{
    return this->triggerClick(eventManager)
        || this->triggerKey(eventManager)
        || this->triggerMouseMove(eventManager);
}
