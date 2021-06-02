/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#include "AbstractScene.hpp"

using namespace Engine;

AbstractScene::AbstractScene(IEventManager &eventManager, SystemManager &systemManager,
    EntityManager &entityManager)
    : _eventManager(eventManager), _systemManager(systemManager), _entityManager(entityManager)
{
}

AbstractScene::~AbstractScene()
{
}
