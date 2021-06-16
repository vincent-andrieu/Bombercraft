/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** AIComponent.hpp
*/

#include "Game/IABomberman/IABomberman.hpp"

#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

namespace Component
{
    class AIComponent : public Engine::Component<AIComponent>
    {
        public:
            AIComponent();
            virtual ~AIComponent() = default;

        private:
            std::shared_ptr<GameModule::IABomberman> _AI;
    };
}

#endif