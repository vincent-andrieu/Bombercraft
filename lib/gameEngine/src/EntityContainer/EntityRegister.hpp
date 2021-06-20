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
#include <algorithm>
#include <numeric>
#include <stdexcept>
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
        bool isSet(Entity entity);

      private:
        std::vector<Signature> _entitySignatures;
        std::vector<Entity> _freeEntities;
    };
} // namespace Engine

#endif // ENTITYREGISTER_HPP