/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 TimerSystem.hpp.h
*/

#ifndef TIMERSYSTEM_HPP
#define TIMERSYSTEM_HPP

#include "env.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "components/Timer.hpp"
#include "EntityManager/EntityManager.hpp"

namespace Engine
{
    class TimerSystem : public AbstractSystem {
      public:
        TimerSystem(EntityManager &entityManager);

        void update();
    };
}

#endif // TIMERSYSTEM_HPP
