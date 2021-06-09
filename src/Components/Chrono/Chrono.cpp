/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 Chrono.cpp.cc
*/

#include "Chrono.hpp"
#include "Game/CoreData/CoreData.hpp"

Component::Chrono::Chrono(double seconds, Engine::scriptHandler handler)
    : seconds(seconds), _script(*Game::CoreData::entityManager, *Game::CoreData::sceneManager, handler)
{
}

void Component::Chrono::trigger(Engine::Entity entity)
{
    this->_script.trigger(entity);
}
