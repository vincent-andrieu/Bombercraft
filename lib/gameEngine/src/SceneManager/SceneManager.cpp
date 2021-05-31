/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

using namespace Engine;

SceneManager::SceneManager(IEventManager &events, EntityManager<MAX_COMPONENT> &entityManager) :
    _events(events), _entityManager(entityManager), _scene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

