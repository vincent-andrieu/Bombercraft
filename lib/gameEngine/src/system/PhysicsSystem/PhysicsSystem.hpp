/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 PhysicsSystem.hpp.h
*/

#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "env.hpp"
#include "System/System.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

class PhysicsSystem : public System<MAX_COMPONENT, MAX_SYSTEM> {
  public:
    PhysicsSystem(EntityManager<MAX_COMPONENT, MAX_SYSTEM> &entityManager);

    void update(float dt);

  private:
    EntityManager<MAX_COMPONENT, MAX_SYSTEM>& _entityManager;
};

#endif // PHYSICSSYSTEM_HPP
