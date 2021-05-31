/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#include "AbstractScene.hpp"

AbstractScene::AbstractScene(IEventManager &events, SystemManager &systemManager, EntityManager<MAX_COMPONENT, MAX_SYSTEM> &entityManager) :
    _events(events), _systemManager(systemManager), _entityManager(entityManager)
{
}

AbstractScene::~AbstractScene()
{
}
