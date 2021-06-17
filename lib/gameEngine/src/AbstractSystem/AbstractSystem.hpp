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
#include <mutex>
#include "env.hpp"
#include "entity.hpp"

namespace Engine
{
    class EntityManager;

    class AbstractSystem {
      public:
        AbstractSystem(EntityManager &entityManager);
        AbstractSystem(const AbstractSystem &src);
        virtual ~AbstractSystem() = default;

        void onEntityUpdated(Entity entity, const Signature &components);

        template <typename... Ts> void setRequirements();

        void onEntityRemoved(Entity entity);
        void addEntity(Entity entity);
        void removeEntity(Entity entity);

        virtual void onManagedEntityAdded(Entity){};
        virtual void onManagedEntityRemoved(Entity){};

      protected:
        const std::vector<Entity> getManagedEntities();
        EntityManager &_entityManager;

      private:
        Signature _requirements;
        std::vector<Entity> _managedEntities;
        std::unordered_map<Entity, Index> _entityToManagedEntity;
        std::mutex _mutex;
    };
} // namespace Engine

#include "EntityManager/EntityManager.hpp"

namespace Engine
{
    template <typename... Ts> void AbstractSystem::setRequirements()
    {
        (_requirements.set(Ts::type), ...);
    }
} // namespace Engine

#endif // ABSTRACTSYSTEM_HPP
