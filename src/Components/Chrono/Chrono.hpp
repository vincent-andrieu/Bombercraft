/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 Chrono.hpp.h
*/

#ifndef CHRONO_HPP
#define CHRONO_HPP

#include "GameEngine.hpp"

namespace Component
{
    class Chrono : public Engine::Component<Chrono> {
      public:
        Chrono(double seconds, Engine::scriptHandler handler);
        virtual ~Chrono() = default;

        double seconds;

        void trigger(Engine::Entity entity);
      private:
        Engine::Script _script;
    };
}

#endif // CHRONO_HPP
