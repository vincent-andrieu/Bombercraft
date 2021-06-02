/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Timer.hpp.h
*/

#ifndef TIMER_HPP
#define TIMER_HPP

#include "Component/Component.hpp"
#include "Script.hpp"
#include <chrono>

namespace Engine
{
    template <typename... Args>
    class Timer : public Component {
      public:
        Timer(std::size_t time) : interval(time), start(std::chrono::system_clock::now()) {}
        ~Timer() = default;

        void start()
        {
            start = std::chrono::system_clock::now();
        }

        bool eval(Entity entity)
        {
            std::chrono::system_clock now = std::chrono::system_clock::now();
            std::chrono::milliseconds t = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch() - start.time_since_epoch());

            if (t >= interval) {
                start = std::chrono::system_clock::now();
                script(entity);
                return true;
            }
            return false;
        }

        std::chrono::milliseconds interval;
        std::chrono::system_clock::time_point start;
        Script<Args> script;
    };
}

#endif // TIMER_HPP
