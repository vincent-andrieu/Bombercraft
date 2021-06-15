/*
 * EPITECH PROJECT, 2021
 * RessourcePack
 * File description:
 * RessourcePackSystem.hpp - Created: 15/06/2021
 */

#ifndef RESSOURCE_PACK_SYSTEM_HPP
#define RESSOURCE_PACK_SYSTEM_HPP

#include "Game/Core/Core.hpp"
#include "EntityManager/EntityManager.hpp"

namespace System
{
    class RessourcePackSystem : public Engine::AbstractSystem {
      public:
        RessourcePackSystem();

        void set(const string &ressourcePack);
    };
} // namespace System

#endif