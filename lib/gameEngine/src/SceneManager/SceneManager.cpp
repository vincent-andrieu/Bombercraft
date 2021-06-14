/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

using namespace Engine;

SceneManager::SceneManager() : _currentScene(nullptr), _nextScene(nullptr)
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

void SceneManager::run(std::shared_ptr<AbstractScene> scene)
{
    if (scene != nullptr) {
        scene->update();
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

void SceneManager::updateScene()
{
    if (_nextScene != nullptr) {
        this->setCurrentScene(_nextScene);
        _nextScene = nullptr;
    }
}

std::shared_ptr<AbstractScene> SceneManager::getLastScene()
{
    return _lastScene;
}

void SceneManager::setScene(const std::shared_ptr<AbstractScene> &scene)
{
    if (std::find(_scenes.begin(), _scenes.end(), scene) == _scenes.end())
        return;
    _lastScene = _currentScene;
    _nextScene = scene;
}