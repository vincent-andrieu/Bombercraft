/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 AbstractEvent.cpp.cc
*/

#include "AbstractEvent.hpp"

Component::AbstractEvent::AbstractEvent(Engine::SceneManager &sceneManager,
    eventScript &handler, Game::EventRequirement &requirements)
    : _sceneManager(sceneManager), _handler(handler), _requirements(requirements)
{
}

void Component::AbstractEvent::trigger(Engine::EntityManager &entityManager,
    raylib::Input &eventManager, Engine::Entity entity)
{
//    if (_requirements.isTrigger(eventManager)) {
//        _hander(entityManager, _sceneManager, eventManager, entity);
//    }
}
