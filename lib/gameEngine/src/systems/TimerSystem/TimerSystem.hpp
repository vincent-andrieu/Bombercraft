/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 TimerSystem.hpp.h
*/

#ifndef TIMERSYSTEM_HPP
#define TIMERSYSTEM_HPP

#include "AbstractSystem/AbstractSystem.hpp"
#include "EntityManager/EntityManager.hpp"
#include "components/Timer.hpp"

namespace Engine
{
    class TimerSystem : public AbstractSystem {
      public:
        TimerSystem(EntityManager &entityManager);
        ~TimerSystem() = default;

        void update();
    };
}

#endif // TIMERSYSTEM_HPP
