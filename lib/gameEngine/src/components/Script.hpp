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
    using scriptHandler = std::function<void(Engine::EntityManager&, Engine::SceneManager&, const Engine::Entity)>;

    class Script : public Component<Script> {
      public:
        Script(EntityManager &entityManager, SceneManager &sceneManager, scriptHandler &handler)
            : _handler(handler), _entityManager(entityManager), _sceneManager(sceneManager)
        {}

        virtual ~Script() = default;

        void trigger(const Entity entity)
        {
            _handler(_entityManager.get(), _sceneManager.get(), entity);
        }

      private:
        scriptHandler _handler;
        std::reference_wrapper<EntityManager> _entityManager;
        std::reference_wrapper<SceneManager> _sceneManager;
    };
} // namespace Engine

#endif // ABSTRACTEVENT_HPP