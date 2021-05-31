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
        void add(Args &&...args);

        template <typename T>
        void remove();

        protected:
        private:
            IEventManager &_events;
            EntityManager<MAX_COMPONENT> &_entityManager;
            std::vector<std::shared_ptr<AbstractScene>> _scenes;
            std::shared_ptr<AbstractScene> _scene;
            std::string sceneName;
    };

    template <typename T, typename... Args>
    void SceneManager::add(Args &&...args)
    {
        _scenes.push_back(std::make_shared<T>(std::forward<Args>(args)...));
        if (_scene == nullptr)
            _scene = _scenes.back();
    }

    template <typename T>
    void SceneManager::remove()
    {
        for (std::shared_ptr<AbstractScene> elem : _scenes) {
            if ()
        }
    }

}



#endif /* !SCENEMANAGER_HPP_ */
