/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 TimeText.hpp.h
*/

#ifndef TIMETEXT_HPP
#define TIMETEXT_HPP

#include "raylib.hpp"
#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"

namespace GUI
{
    class TimeText : public raylib::Text {
      public:
        TimeText(Engine::Entity owner, const std::string &text, const raylib::MyVector2 position = {0, 0}, const std::size_t size = 1,
            const raylib::RColor color = raylib::RColor::RWHITE, const std::string &fontPath = "");

        void setTime(double const& time);

      private:
        Engine::Timer &_timerComponent;
    };
} // namespace GUI

#endif // TIMETEXT_HPP
