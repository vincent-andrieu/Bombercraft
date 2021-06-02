/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 TimerSystem.cpp.cc
*/

#include "TimerSystem.hpp"

using namespace Engine;

TimerSystem::TimerSystem(EntityManager &entityManager)
    : Engine::AbstractSystem(entityManager)
{
    this->setRequirements<Timer>();
}

void TimerSystem::update()
{
}
