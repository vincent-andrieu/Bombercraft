/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventRequirement.cpp.cc
*/

#include "EventRequirement.hpp"

#include <utility>

Game::EventRequirement::EventRequirement(bool mouseMove) : _click(0), _mouseMoveEvent(mouseMove)
{
}

Game::EventRequirement::EventRequirement(std::vector<raylib::KeyBoard> keyPress, std::vector<raylib::KeyBoard> keyRelease)
    : _click(0), _mouseMoveEvent(false), _handledKeyReleased(keyRelease), _handledKeyPress(keyPress)
{
}

Game::EventRequirement::EventRequirement(uint click) : _click(click), _mouseMoveEvent(false)
{
}

bool Game::EventRequirement::triggerClick(raylib::Input &eventManager) const
{
    if (!_click)
        return false;
    if ((_click & CLK_LEFT) && eventManager.isMouseLeftPressed()) {
        return true;
    }
    if ((_click & CLK_RIGHT) && eventManager.isMouseRightPressed()) {
        return true;
    }
    if ((_click & CLK_MIDDLE) && eventManager.isMouseMiddlePressed()) {
        return true;
    }
    return false;
}

bool Game::EventRequirement::triggerKey(raylib::Input &eventManager) const
{
    if (!_handledKeyReleased.empty()) {
        for (const auto &key : _handledKeyReleased) {
            if (eventManager.isKeyReleased(key)) {
                return true;
            }
        }
    }
    if (!_handledKeyPress.empty()) {
        for (const auto &key : _handledKeyPress) {
            if (eventManager.isKeyPressed(key)) {
                return true;
            }
        }
    }
    return false;
}

bool Game::EventRequirement::triggerMouseMove([[maybe_unused]] raylib::Input &eventManager) const
{
    return _mouseMoveEvent;
}

bool Game::EventRequirement::isTriggered(raylib::Input &eventManager) const
{
    return this->triggerClick(eventManager) || this->triggerMouseMove(eventManager) || this->triggerKey(eventManager);
}
