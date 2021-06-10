/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 ClickFocusEvent.hpp
*/

#ifndef CLICKFOCUSEVENT_HPP
#define CLICKFOCUSEVENT_HPP

#include "Components/AbstractEvent/AbstractEvent.hpp"
#include "GameEngine.hpp"

namespace Component {
    class ClickFocusEvent : public AbstractEvent, public Engine::Component<ClickFocusEvent> {
      public:
        ClickFocusEvent(eventScript &handler, Game::EventRequirement const &requirements);

        bool getFocus() const;
        void changeFocus(bool focus);
      private:
        bool _isFocus;

    };
}

#endif // CLICKFOCUSEVENT_HPP