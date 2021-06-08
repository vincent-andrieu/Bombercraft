/*
** EPITECH PROJECT, 2021
** ClickEvent.cpp
** File description:
** Click event variable
*/

#include "Game/EventRequirement/EventRequirement.hpp"
#include "ClickEvent.hpp"

static const Game::EventRequirement my_event(Game::evtMouse::LEFT);

Component::ClickEvent::ClickEvent(eventScript &handler) : AbstractEvent(handler, my_event)
{
}