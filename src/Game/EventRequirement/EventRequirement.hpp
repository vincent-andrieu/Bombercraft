/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 EventRequirement.hpp
*/

#ifndef EVENTREQUIREMENT_HPP
#define EVENTREQUIREMENT_HPP

#include "raylib.hpp"
#ifdef _WIN32
typedef unsigned int uint;
#endif
#include <vector>

namespace Game
{
    enum MouseEventType : uint
    {
        CLK_NONE = 0b0,
        CLK_LEFT = 0b1,
        CLK_RIGHT = 0b10,
        CLK_MIDDLE = 0b100
    };

    class EventRequirement {
      public:
        EventRequirement() = delete;
        explicit EventRequirement(uint click);
        explicit EventRequirement(std::vector<raylib::KeyBoard> keyPress, std::vector<raylib::KeyBoard> keyRelease);
        explicit EventRequirement(bool mouseMove);

        bool isTriggered(raylib::Input &eventManager) const;

      private:
        bool triggerClick(raylib::Input &eventManager) const;
        bool triggerKey(raylib::Input &eventManager) const;
        bool triggerMouseMove(raylib::Input &eventManager) const;

      private:
        const uint _click{0};
        const bool _mouseMoveEvent{false};
        const std::vector<raylib::KeyBoard> _handledKeyReleased{};
        const std::vector<raylib::KeyBoard> _handledKeyPress{};
    };
} // namespace Game

#endif // EVENTREQUIREMENT_HPP