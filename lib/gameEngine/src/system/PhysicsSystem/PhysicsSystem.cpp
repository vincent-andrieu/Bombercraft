/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 PhysicsSystem.cpp.cc
*/

#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(EntityManager<32, 8> &entityManager)
    : _entityManager(entityManager)
{
    this->setRequirements<Position, Velocity>();
}

void PhysicsSystem::update(float dt)
{
    for (const auto &entity : this->getManagedEntities()) {
        auto [position, velocity] = _entityManager.getComponents<Position, Velocity>(entity);
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
    }
}
