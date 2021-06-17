/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 TimerSystem.cpp.cc
*/

#include "TimerSystem.hpp"

using namespace Engine;

TimerSystem::TimerSystem(EntityManager &entityManager) : AbstractSystem(entityManager)
{
    this->setRequirements<Timer>();
}

void TimerSystem::update()
{
    for (const Entity &entity : this->getManagedEntities()) {
        auto &timer = this->_entityManager.getComponent<Timer>(entity);
        timer.eval(entity);
    }
}

void TimerSystem::pause()
{
    for (const Entity &entity : this->getManagedEntities()) {
        auto &timer = this->_entityManager.getComponent<Timer>(entity);
        timer.pause();
    }
}

void TimerSystem::resume()
{
    for (const Entity &entity : this->getManagedEntities()) {
        auto &timer = this->_entityManager.getComponent<Timer>(entity);
        timer.resume();
    }
}