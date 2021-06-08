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

namespace Engine
{
    class PhysicsSystem : public AbstractSystem {
      public:
        PhysicsSystem(EntityManager &entityManager);

        void update(float dt);
    };
}

#endif // PHYSICSSYSTEM_HPP
