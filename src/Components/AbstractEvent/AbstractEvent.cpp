/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 AbstractEvent.cpp.cc
*/

#include "AbstractEvent.hpp"

Component::AbstractEvent::AbstractEvent(eventScript &handler, const Game::EventRequirement &requirements)
    : _handler(handler), _requirements(requirements)
{
}

void Component::AbstractEvent::trigger(Engine::Entity entity)
{
    if (Game::CoreData::eventManager && _requirements.get().isTriggered(*Game::CoreData::eventManager)) {
        (_handler.get())(entity);
    }
}