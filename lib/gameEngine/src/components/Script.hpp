/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Script.hpp.h
*/

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "Component/Component.hpp"

namespace Engine
{
    template <typename... Args>
    class Script : public Component<Script<Args>> {
      public:
        Event(std::function<void(Args...)> &handler) : handler(handler)
        {
        }
        ~Event() = default;

        std::function<void(Args...)> &handler;
    };
}

#endif // EVENT_HPP
