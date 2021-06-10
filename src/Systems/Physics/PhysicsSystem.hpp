/*
 * EPITECH PROJECT, 2021
 * Physic
 * File description:
 * PhysicsSystem.hpp - Created: 10/06/2021
 */

#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include "Game/Core/Core.hpp"
#include "EntityManager/EntityManager.hpp"
#include "IMovable.hpp"

namespace System
{
    class PhysicsSystem : public Engine::AbstractSystem {
      public:
        PhysicsSystem();

        void update(float dt);
    };
} // namespace System

#endif
