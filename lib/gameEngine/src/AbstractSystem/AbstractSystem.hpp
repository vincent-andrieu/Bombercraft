/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 AbstractSystem.hpp.h
*/

#ifndef ABSTRACTSYSTEM_HPP
#define ABSTRACTSYSTEM_HPP

#include <cctype>
#include <vector>
#include <unordered_map>
#include "env.hpp"
#include "entity.hpp"

namespace Engine
{
    class AbstractSystem {
      public:
        AbstractSystem();
        virtual ~AbstractSystem() = default;

        void onEntityUpdated(Entity entity, const Signature &components);

        template <typename... Ts> void setRequirements()
        {
            (_requirements.set(Ts::type), ...);
        }

        void onEntityRemoved(Entity entity);
        void addEntity(Entity entity);
        void removeEntity(Entity entity);

        virtual void onManagedEntityAdded(Entity entity) = 0;

        virtual void onManagedEntityRemoved(Entity entity) = 0;

        const std::size_t type;

        static std::size_t instanceCounter;
      protected:
        const std::vector<Entity> &getManagedEntities() const;

      private:
        Signature _requirements;
        std::vector<Entity> _managedEntities;
        std::unordered_map<Entity, Index> _entityToManagedEntity;
    };
}

#endif // ABSTRACTSYSTEM_HPP
