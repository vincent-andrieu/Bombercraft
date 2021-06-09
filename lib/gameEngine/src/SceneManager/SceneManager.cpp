/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

using namespace Engine;

SceneManager::SceneManager()
    : _currentScene(nullptr)
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

std::shared_ptr<AbstractScene> SceneManager::getCurrentScene()
{
    return _currentScene;
}

void SceneManager::setCurrentScene(std::shared_ptr<AbstractScene> scene)
{
    if (_currentScene != nullptr) {
        _currentScene->close();
    }
    _currentScene = scene;
    if (_currentScene) {
        _currentScene->open();
    }
}