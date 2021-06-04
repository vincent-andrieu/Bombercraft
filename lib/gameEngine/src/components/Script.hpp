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
    using scriptHandler = std::function<void(Engine::EntityManager, Engine::SceneManager, const Engine::Entity)>;

    class Script : public Component<Script> {
      public:
        Script(EntityManager &entityManager, SceneManager &sceneManager, scriptHandler &handler)
            : handler(handler), _entityManager(entityManager), _sceneManager(sceneManager)
        {
        }

        ~Script() = default;

        void trigger(const Entity entity)
        {
            handler(_entityManager, _sceneManager, entity);
        }

      private:
        scriptHandler &handler;
        EntityManager &_entityManager;
        SceneManager &_sceneManager;
    };
} // namespace Engine

#endif // ABSTRACTEVENT_HPP