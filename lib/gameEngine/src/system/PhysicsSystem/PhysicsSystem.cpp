/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 PhysicsSystem.cpp.cc
*/

#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(EntityManager<MAX_COMPONENT> &entityManager)
    : _entityManager(entityManager)
{
    this->setRequirements<Position, Velocity>();
}

void PhysicsSystem::update(float dt)
{
    for (const Entity &entity : this->getManagedEntities()) {
        auto [position, velocity] = _entityManager.getComponents<Position, Velocity>(entity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
    }
}

void PhysicsSystem::onManagedEntityAdded(Entity entity)
{
}
void PhysicsSystem::onManagedEntityRemoved(Entity entity)
{
}
