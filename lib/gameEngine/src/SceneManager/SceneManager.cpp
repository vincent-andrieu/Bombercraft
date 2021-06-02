/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

using namespace Engine;

SceneManager::SceneManager(IEventManager &events, EntityManager &entityManager)
    : _eventManager(events), _entityManager(entityManager), _currentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::run()
{
    if (_currentScene != nullptr) {
        _currentScene->update();
    }
}