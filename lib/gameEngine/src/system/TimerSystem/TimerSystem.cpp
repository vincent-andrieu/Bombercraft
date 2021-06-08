/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 TimerSystem.cpp.cc
*/

#include "TimerSystem.hpp"

using namespace Engine;

TimerSystem::TimerSystem(EntityManager &entityManager) : AbstractSystem(entityManager)
{
    this->setRequirements<Timer>();
}

void TimerSystem::update()
{
    std::cout << "TIMER SYS !!\n";
    for (const Entity &entity : this->getManagedEntities()) {
        auto timer = this->_entityManager.getComponent<Timer>(entity);
        std::cout << "TIMER EVAL\n";
        timer.eval(entity);
    }
}