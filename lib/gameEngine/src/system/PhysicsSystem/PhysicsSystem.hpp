/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 PhysicsSystem.hpp.h
*/

#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "env.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "EntityManager/EntityManager.hpp"

class PhysicsSystem : public AbstractSystem {
  public:
    PhysicsSystem(EntityManager<MAX_COMPONENT> &entityManager);

    void update(float dt);

    virtual void onManagedEntityAdded(Entity entity);

    virtual void onManagedEntityRemoved(Entity entity);

  private:
    EntityManager<MAX_COMPONENT>& _entityManager;
};

#endif // PHYSICSSYSTEM_HPP
