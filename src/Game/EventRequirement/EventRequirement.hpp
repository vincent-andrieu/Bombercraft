/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventRequirement.hpp.h
*/

#ifndef EVENTREQUIREMENT_HPP
#define EVENTREQUIREMENT_HPP

#include "raylib.hpp"
#include <vector>

namespace Game {
    enum class evtMouse {
        LEFT = 1,
        RIGHT = 2,
        MIDDLE = 4
    };
    using clickType = uint8_t;

    clickType operator|(evtMouse a, evtMouse b);
    clickType operator|(clickType a, evtMouse b);

    class EventRequirement {
      public:
        EventRequirement(clickType const click = 0, bool mouseMove = false,
            std::vector<raylib::KeyBoard> const &keyPress = {},
            std::vector<raylib::KeyBoard> const &keyRelease = {});

        bool isTrigger(raylib::Input &eventManager) const;

      private:
        bool triggerClick(raylib::Input &eventManager) const;
        bool triggerKey(raylib::Input &eventManager) const;
        bool triggerMouseMove(raylib::Input &eventManager) const;

      private:
        const clickType _click;
        const bool _mouseMoveEvent;
        const std::vector<raylib::KeyBoard> _handledKeyPress;
        const std::vector<raylib::KeyBoard> _handledKeyRelease;
    };
}

#endif // EVENTREQUIREMENT_HPP
