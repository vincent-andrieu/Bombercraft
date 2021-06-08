/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventRequirement.hpp
*/

#ifndef EVENTREQUIREMENT_HPP
#define EVENTREQUIREMENT_HPP

#include "raylib.hpp"
#include <vector>

namespace Game
{
    enum class evtMouse : uint
    {
        NONE = 0,
        LEFT = 1,
        RIGHT = 2,
        MIDDLE = 4
    };

    uint operator|(evtMouse a, evtMouse b);
    uint operator|(uint a, evtMouse b);

    class EventRequirement {
      public:
        EventRequirement() = delete;
        explicit EventRequirement(const uint &click = 0,
            bool mouseMove = false,
            std::vector<raylib::KeyBoard> keyPress = {},
            std::vector<raylib::KeyBoard> keyRelease = {});
        explicit EventRequirement(const evtMouse &click = Game::evtMouse::NONE,
            bool mouseMove = false,
            std::vector<raylib::KeyBoard> keyPress = {},
            std::vector<raylib::KeyBoard> keyRelease = {});

        bool isTriggered(raylib::Input &eventManager) const;

      private:
        bool triggerClick(raylib::Input &eventManager) const;
        bool triggerKey(raylib::Input &eventManager) const;
        bool triggerMouseMove(raylib::Input &eventManager) const;

      private:
        const uint _click;
        const bool _mouseMoveEvent{false};
        const std::vector<raylib::KeyBoard> _handledKeyPress;
        const std::vector<raylib::KeyBoard> _handledKeyRelease;
    };
} // namespace Game

#endif // EVENTREQUIREMENT_HPP