/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

#include <utility>

using namespace Engine;

void SceneManager::run()
{
    if (_currentScene != nullptr) {
        _currentScene->update();
    }
}

void SceneManager::run(const std::shared_ptr<AbstractScene> &scene)
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
    if (_currentScene) {
        if (_toClose) {
            _currentScene->close();
        } else {
            _unclosedScenes.push(_currentScene);
        }
    }
    _currentScene = std::move(scene);
    if (_currentScene && _toOpen) {
        _currentScene->open();
    }
    _toClose = true;
    _toOpen = true;
}

void SceneManager::updateScene()
{
    if (_nextScene != nullptr) {
        this->setCurrentScene(_nextScene);
        _nextScene = nullptr;
    }
}

void SceneManager::pushLastScene()
{
    _lastScenes.push(_currentScene);
}

std::shared_ptr<AbstractScene> SceneManager::peekLastScene()
{
    std::shared_ptr<AbstractScene> my_last(_lastScenes.top());
    _lastScenes.pop();
    return my_last;
}

void SceneManager::popLastScene()
{
    _lastScenes.pop();
}

void SceneManager::setScene(const std::shared_ptr<AbstractScene> &scene, const bool close, const bool open)
{
    if (std::find(_scenes.begin(), _scenes.end(), scene) == _scenes.end())
        return;
    _toClose = close;
    _toOpen = open;
    if (_currentScene == nullptr) {
        this->setCurrentScene(scene);
    } else {
        _nextScene = scene;
    }
}

void SceneManager::closeLastUnclosedScene()
{
    std::shared_ptr<AbstractScene> my_scene(nullptr);

    if (_unclosedScenes.empty())
        return;
    my_scene = _unclosedScenes.top();
    if (!my_scene)
        return;
    std::cout << "closing" << std::endl;
    _unclosedScenes.pop();
    my_scene->close();
}