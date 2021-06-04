/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 MouseMoveEvent.hpp.h
*/

#ifndef MOUSEMOVEEVENT_HPP
#define MOUSEMOVEEVENT_HPP

#include "Components/AbstractEvent/AbstractEvent.hpp"
#include "GameEngine.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"

namespace Component {
    class MouseMoveEvent : public AbstractEvent, public Engine::Component<MouseMoveEvent> {
      public:
        MouseMoveEvent(eventScript &handler, std::shared_ptr<Game::EventRequirement> requirements)
            : AbstractEvent(handler, requirements)
        {}
    };
}

#endif // MOUSEMOVEEVENT_HPP
