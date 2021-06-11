/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventRequirement.cpp.cc
*/

#include "EventRequirement.hpp"

#include <utility>

Game::EventRequirement::EventRequirement(
    const uint &click, bool mouseMove, std::vector<raylib::KeyBoard> keyPress, std::vector<raylib::KeyBoard> keyRelease)
    : _click(click), _mouseMoveEvent(mouseMove), _handledKeyPress(std::move(keyPress)), _handledKeyRelease(std::move(keyRelease))
{
}

Game::EventRequirement::EventRequirement(
    const Game::evtMouse &click, bool mouseMove, std::vector<raylib::KeyBoard> keyPress, std::vector<raylib::KeyBoard> keyRelease)
    : _click((int) Game::evtMouse::NONE | click), _mouseMoveEvent(mouseMove), _handledKeyPress(std::move(keyPress)),
      _handledKeyRelease(std::move(keyRelease))
{
}

bool Game::EventRequirement::triggerClick(raylib::Input &eventManager) const
{
    if (!_click)
        return false;
    if ((_click & (int) evtMouse::LEFT) && eventManager.isMouseLeftPressed()) {
        return true;
    }
    if ((_click & (int) evtMouse::RIGHT) && eventManager.isMouseRightPressed()) {
        return true;
    }
    if ((_click & (int) evtMouse::MIDDLE) && eventManager.isMouseMiddlePressed()) {
        return true;
    }
    return false;
}

bool Game::EventRequirement::triggerKey(raylib::Input &eventManager) const
{
    //    for (const auto &key : _handledKeyRelease) {
    //        if (eventManager.isKeyReleased(key)) {
    //            return true;
    //        }
    //    }
    //    for (const auto &key : _handledKeyPress) {
    //        if (eventManager.isKeyPressed(key)) {
    //            return true;
    //        }
    //    }
    return false;
}

bool Game::EventRequirement::triggerMouseMove([[maybe_unused]] raylib::Input &eventManager) const
{
    return _mouseMoveEvent;
}

bool Game::EventRequirement::isTriggered(raylib::Input &eventManager) const
{
    return this->triggerClick(eventManager) || this->triggerKey(eventManager) || this->triggerMouseMove(eventManager);
}

uint Game::operator|(Game::evtMouse a, Game::evtMouse b)
{
    return static_cast<uint>(a) | static_cast<uint>(b);
}

uint Game::operator|(uint a, Game::evtMouse b)
{
    return a | static_cast<uint>(b);
}