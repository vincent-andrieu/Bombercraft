/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include "AbstractScene/AbstractScene.hpp"
#include "IEventManager.hpp"
#include "EntityManager.hpp"
#include "env.hpp"
#include <vector>

namespace Engine
{
    class SceneManager {
        public:
            SceneManager(IEventManager &events, EntityManager<MAX_COMPONENT> &entityManager);
            ~SceneManager();

        void run();

        template <typename T, typename... Args>
        void createScene(Args &&...args);

        template <typename T>
        void remove();

        template <typename T>
        void setScene();

        protected:
        private:
            IEventManager &_events;
            EntityManager<MAX_COMPONENT> &_entityManager;
            std::vector<std::shared_ptr<AbstractScene>> _scenes;
            std::vector<std::reference_wrapper<const std::type_info>> _types;
            std::shared_ptr<AbstractScene> _scene;
            std::string sceneName;
    };

    template <typename T, typename... Args>
    void SceneManager::createScene(Args &&...args)
    {
        const std::type_info &type = typeid(T);

        if (std::find_if(_types.begin(), _types.end(),
                [&type](auto &sysType) {
                    return systType.get() == type;
                }))
            != _types.end() {
                throw std::exception();
        }
        auto &scene = _scenes.push_back(std::make_shared<T>(std::forward<Args>(args)...));
        _types.emplace_back(typeid(T));
        if (_scene == nullptr)
            _scene = _scenes.back();
    }

    template <typename T>
    void SceneManager::remove()
    {
        std::size_t index = 0;
        const std::type_info &type = typeid(T);
        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sysType) {
            return sysType.get() == type;
        });

        if (type_it == _types.end()) {
            throw std::exception();
        }
        index = std:distance(_types.begin(), type_it);
        if (_scene == _scenes[index]) {
            _scene = (_scenes.size()) ? _scenes.front() : nullptr;
        }
        _types[index] = _types.back();
        _types.pop_back();
        _scene[index] = _types.back();
        _scene.pop_back();
    }

    template <typename T>
    void SceneManager:setScene()
    {
        std::size_t index = 0;
        const std::type_info &type = typeid(T);
        auto type_it = std::find_if(_types.begin(), _types.end(), [&type](auto &sysType) {
            return sysType.get() == type;
        });

        if (type_it == _types.end()) {
            throw std::exception();
        }
        index = std:distance(_types.begin(), type_it);
        _scene = _scenes[index];
    }

}



#endif /* !SCENEMANAGER_HPP_ */
