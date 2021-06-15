/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 KeyEvent.hpp
*/

#ifndef KEYEVENT_HPP
#define KEYEVENT_HPP

#include "Components/AbstractEvent/AbstractEvent.hpp"
#include "GameEngine.hpp"

namespace Component
{
    class KeyEvent : public AbstractEvent, public Engine::Component<KeyEvent> {
      public:
        KeyEvent(eventScript handler, const Game::EventRequirement &requirements) : AbstractEvent(handler, requirements)
        {
        }

        virtual ~KeyEvent() = default;
    };
} // namespace Matrix2D

#endif // KEYEVENT_HPP