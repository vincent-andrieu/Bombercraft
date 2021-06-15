/*
 * EPITECH PROJECT, 2021
 * RessourcePack
 * File description:
 * RessourcePackComponent.hpp - Created: 15/06/2021
 */

#ifndef RESSOURCE_PACK_COMPONENT_HPP
#define RESSOURCE_PACK_COMPONENT_HPP

#include "GameEngine.hpp"
#include "raylib.hpp"

namespace Component
{
    class RessourcePack : public Engine::Component<RessourcePack> {
      public:
        RessourcePack(const string &ressourcePack);
        virtual ~RessourcePack() = default;

        void set(const string &ressourcePack);

      private:
        string _ressourcePack;
    };
} // namespace Component

#endif