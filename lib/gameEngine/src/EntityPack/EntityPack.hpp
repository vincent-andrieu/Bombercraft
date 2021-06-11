/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 EntityPack.hpp.h
*/

#ifndef ENTITYPACK_HPP
#define ENTITYPACK_HPP

#include "EntityManager/EntityManager.hpp"
#include <unordered_map>
#include <string>
#include <vector>

namespace Engine
{
    class EntityPack {
      public:
        EntityPack(EntityManager &entityManager);
        ~EntityPack();

        void unload();

        Entity createEntity(const std::string &key);
        Entity createAnonymousEntity();

        void removeEntity(const std::string &key);

        Entity getEntity(const std::string &key);

      private:
        std::unordered_map<std::string, Entity> _entities;
        std::vector<Entity> _anonymousEntities;
        EntityManager &_entityManager;
    };
}

#endif // ENTITYPACK_HPP
