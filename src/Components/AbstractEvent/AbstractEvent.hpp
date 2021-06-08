/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 AbstractEvent.hpp.h
*/

#ifndef ABSTRACTEVENT_HPP
#define ABSTRACTEVENT_HPP

#include "Game/CoreData/CoreData.hpp"

#include "GameEngine.hpp"
#include "raylib.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"

namespace Component
{
    using eventScript = std::function<void(const Engine::Entity)>;

    class AbstractEvent {
      public:
        AbstractEvent(eventScript &handler, const Game::EventRequirement &requirements);

        void trigger(Engine::Entity entity);

      private:
        std::reference_wrapper<eventScript> _handler;
        std::reference_wrapper<const Game::EventRequirement> _requirements;
    };
} // namespace Component

#endif // ABSTRACTEVENT_HPP