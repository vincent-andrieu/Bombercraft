/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include <vector>
#include <stack>
#include "AbstractScene/AbstractScene.hpp"
#include "EntityManager/EntityManager.hpp"
#include "env.hpp"

namespace Engine
{
    class SceneManager {
      public:
        SceneManager();
        ~SceneManager();

        void run();
        void run(std::shared_ptr<AbstractScene> scene);

        template <typename T, typename... Args> void createScene(Args &&...sceneType);

        template <typename T> void remove();

        template <typename T> void setScene();
        void setScene(const std::shared_ptr<AbstractScene> &scene);

        void pushLastScene();
        std::shared_ptr<AbstractScene> peekLastScene();
        std::shared_ptr<AbstractScene> getCurrentScene();
        void updateScene();

        template <typename T> std::shared_ptr<AbstractScene> getScene();

      private:
        void setCurrentScene(std::shared_ptr<AbstractScene> scene);

      private:
        std::shared_ptr<AbstractScene> _currentScene;
        std::vector<std::shared_ptr<AbstractScene>> _scenes;
        std::vector<std::reference_wrapper<const std::type_info>> _types;
        std::shared_ptr<AbstractScene> _nextScene;
        std::stack<std::shared_ptr<AbstractScene>> _lastScenes;
    };

    template <typename T, typename... Args> void SceneManager::createScene(Args &&...args)
    {
        const std::type_info &type = typeid(T);

        if (std::find_if(_types.begin(),
                _types.end(),
                [&type](auto &sceneType) {
                    return sceneType.get() == type;
                })
            != _types.end()) {
            throw std::exception();
        }
        _scenes.push_back(std::make_shared<T>(std::forward<Args>(args)...));
        _types.emplace_back(typeid(T));
    }

    template <typename T> void SceneManager::remove()
    {
        std::size_t index = 0;
        const std::type_info &type = typeid(T);
        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sceneType) {
            return sceneType.get() == type;
        });

        if (type_it == _types.end()) {
            throw std::exception();
        }
        index = std::distance(_types.begin(), type_it);
        if (_currentScene == _scenes[index]) {
            this->setCurrentScene((!_scenes.empty()) ? _scenes.front() : nullptr);
        }
        _types[index] = _types.back();
        _types.pop_back();
        _scenes[index] = _scenes.back();
        _scenes.pop_back();
    }

    template <typename T> void SceneManager::setScene()
    {
        std::size_t index = 0;
        const std::type_info &type = typeid(T);
        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sceneType) {
            return sceneType.get() == type;
        });

        if (type_it == _types.end()) {
            throw std::exception();
        }
        index = std::distance(_types.begin(), type_it);
        if (_currentScene == nullptr) {
            this->setCurrentScene(_scenes[index]);
        } else {
            //            _lastScene = _currentScene;
            _nextScene = _scenes[index];
        }
    }

    template <typename T> std::shared_ptr<AbstractScene> SceneManager::getScene()
    {
        std::size_t index = 0;
        const std::type_info &type = typeid(T);
        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sceneType) {
            return sceneType.get() == type;
        });

        if (type_it == _types.end()) {
            throw std::exception();
        }
        index = std::distance(_types.begin(), type_it);
        return _scenes[index];
    }
} // namespace Engine

#endif /* !SCENEMANAGER_HPP_ */