/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 14/06/2021 OptionComponent.hpp.h
*/

#ifndef OPTIONCOMPONENT_HPP
#define OPTIONCOMPONENT_HPP

#include "GameEngine.hpp"

namespace Component
{
    class OptionComponent : public Engine::Component<OptionComponent> {
      public:
        explicit OptionComponent(float volume, const std::string &ressourcePack);
        virtual ~OptionComponent() = default;

        float volume;
        std::string ressourcePack;
    };
} // namespace Component

#endif // OPTIONCOMPONENT_HPP
