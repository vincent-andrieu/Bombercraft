/*
** EPITECH PROJECT, 2021
** ClickEvent.cpp
** File description:
** Click event variable
*/

#include "Game/EventRequirement/EventRequirement.hpp"
#include "ClickEvent.hpp"

Component::ClickEvent::ClickEvent(eventScript handler, const Game::EventRequirement &requirements)
    : AbstractEvent(handler, requirements)
{
}