/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Script.hpp.h
*/

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "Component/Component.hpp"
#include "EntityManager/EntityManager.hpp"
#include "SceneManager/SceneManager.hpp"
#include "entity.hpp"
#include <functional>

namespace Engine
{
    #define SCRIPT_HANDLER std::function<void(EntityManager, SceneManager, Entity)>

    class Script : public Component<Script> {
      public:
        Script(EntityManager &entityManager, SceneManager &sceneManager, SCRIPT_HANDLER &handler)
            : handler(handler), _entityManager(entityManager), _sceneManager(sceneManager)
        {}

        ~Script() = default;

        void trigger(Entity entity)
        {
            handler(_entityManager, _sceneManager, entity);
        }

      private:
        SCRIPT_HANDLER &handler;
        EntityManager &_entityManager;
        SceneManager &_sceneManager;
    };
}

#endif // EVENT_HPP
