/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityRegister.hpp.h
*/

#ifndef ENTITYREGISTER_HPP
#define ENTITYREGISTER_HPP

#include <vector>
#include <bitset>
#include <cstddef>
#include <numeric>
#include "env.hpp"
#include "entity.hpp"
#include "SaveManager/SaveManager.hpp"

namespace Engine
{
    class EntityRegister {
      public:
        EntityRegister() = default;
        ~EntityRegister() = default;

        void allocate(std::size_t size);
        std::vector<Signature> &getEntitySignatures();
        const Signature &getSignature(Entity entity) const;
        Entity create();
        void remove(Entity entity);
        void save(SaveManager &saver) const;

      private:
        std::vector<Signature> _entitySignatures;
        std::vector<Entity> _freeEntities;
        void saveFreeEntities(SaveManager &saver) const;
    };
} // namespace Engine

#endif // ENTITYREGISTER_HPP