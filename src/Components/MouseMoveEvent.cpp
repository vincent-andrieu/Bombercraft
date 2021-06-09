/*
** EPITECH PROJECT, 2021
** MouseMoveEvent.cpp
** File description:
** Implementation of MouseMoveEvent class
*/

#include "MouseMoveEvent.hpp"

using namespace Component;

static const Game::EventRequirement my_requirements(Game::evtMouse::NONE);

MouseMoveEvent::MouseMoveEvent(eventScript &handler) : AbstractEvent(handler, my_requirements)
{
}