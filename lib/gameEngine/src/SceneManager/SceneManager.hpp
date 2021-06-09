/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include "AbstractScene/AbstractScene.hpp"
#include "EntityManager/EntityManager.hpp"
#include "env.hpp"
#include <vector>

namespace Engine
{
    class SceneManager {
        public:
            SceneManager();
            ~SceneManager();

        void run();

        template <typename T, typename... Args>
        void createScene(Args &&...sceneType);

        template <typename T>
        void remove();

        template <typename T>
        void setScene();

        std::shared_ptr<AbstractScene> getCurrentScene();

        private:
            std::shared_ptr<AbstractScene> _currentScene;
            std::vector<std::shared_ptr<AbstractScene>> _scenes;
            std::vector<std::reference_wrapper<const std::type_info>> _types;
    };

    template <typename T, typename... Args>
    void SceneManager::createScene(Args &&...args)
    {
        const std::type_info &type = typeid(T);

        if (std::find_if(_types.begin(), _types.end(),
                [&type](auto &sceneType) {
                    return sceneType.get() == type;
                })
            != _types.end()) {
                throw std::exception();
        }
        _scenes.push_back(std::make_shared<T>(std::forward<Args>(args)...));
        _types.emplace_back(typeid(T));
        if (_currentScene == nullptr)
            _currentScene = _scenes.back();
    }

    template <typename T>
    void SceneManager::remove()
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
            _currentScene = (_scenes.size()) ? _scenes.front() : nullptr;
        }
        _types[index] = _types.back();
        _types.pop_back();
        _scenes[index] = _scenes.back();
        _scenes.pop_back();
    }

    template <typename T>
    void SceneManager::setScene()
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
        _currentScene = _scenes[index];
    }
}



#endif /* !SCENEMANAGER_HPP_ */
