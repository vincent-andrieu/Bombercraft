/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 AbstractEvent.cpp.cc
*/

#include "AbstractEvent.hpp"

Component::AbstractEvent::AbstractEvent(eventScript &handler, const Game::EventRequirement &requirements)
    : _handler(handler), _requirements(std::make_shared<Game::EventRequirement>(requirements))
{
}

void Component::AbstractEvent::trigger(Engine::Entity entity)
{
    if (this->_requirements->isTriggered(*Game::CoreData::eventManager)) {
        this->_handler(entity);
    }
}

void Component::AbstractEvent::setRequirements(const Game::EventRequirement &requirements)
{
    _requirements.reset();
    _requirements = std::make_shared<Game::EventRequirement>(requirements);
}
