/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 AbstractEvent.hpp.h
*/

#ifndef ABSTRACTEVENT_HPP
#define ABSTRACTEVENT_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"

namespace Component
{
    using eventScript = std::function<void(Engine::EntityManager, Engine::SceneManager, raylib::Input, const Engine::Entity)>;

    class AbstractEvent {
      public:
        AbstractEvent(Engine::SceneManager &sceneManager, eventScript &handler,
            Game::EventRequirement &requirements);

        void trigger(Engine::EntityManager &entityManager, raylib::Input &eventManager,
            Engine::Entity entity);

      private:
        std::reference_wrapper<Engine::SceneManager> _sceneManager;
        std::reference_wrapper<eventScript> _handler;
        std::reference_wrapper<Game::EventRequirement> _requirements;
    };
}

#endif // ABSTRACTEVENT_HPP
