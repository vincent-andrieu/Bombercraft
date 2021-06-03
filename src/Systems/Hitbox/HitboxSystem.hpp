/*
 * EPITECH PROJECT, 2021
 * Hitbox
 * File description:
 * HitboxSystem.hpp - Created: 03/06/2021
 */

#ifndef HITBOX_SYSTEM_HPP
#define HITBOX_SYSTEM_HPP

#include "GameEngine.hpp"

namespace System
{
    class HitboxSystem : public Engine::AbstractSystem {
      public:
        HitboxSystem(Engine::EntityManager &entityManager);

        void update();
    };
} // namespace System

#endif