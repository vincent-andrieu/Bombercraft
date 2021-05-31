/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 31/05/2021 AbstractSystem.c
*/

#include "AbstractSystem.hpp"

const std::size_t AbstractSystem::type = generateSystemType();

std::size_t generateSystemType()
{
    static std::size_t count = 0;

    return count++;
}

void AbstractSystem::onEntityUpdated(Entity entity, const Signature &components)
{
    bool satisfied = (_requirements & components) == _requirements;
    bool managed = _entityToManagedEntity.find(entity) != std::end(_entityToManagedEntity);

    if (satisfied && !managed) {
        this->addEntity(entity);
    } else if (!satisfied && managed) {
        this->removeEntity(entity);
    }
}

void AbstractSystem::onEntityRemoved(Entity entity)
{
    if (_entityToManagedEntity.find(entity) != std::end(_entityToManagedEntity)) {
        this->removeEntity(entity);
    }
}

void AbstractSystem::addEntity(Entity entity)
{
    _entityToManagedEntity[entity] = static_cast<Index>(_managedEntities.size());
    _managedEntities.emplace_back(entity);
    this->onManagedEntityAdded(entity);
}

void AbstractSystem::removeEntity(Entity entity)
{
    this->onManagedEntityRemoved(entity);
    auto index = _entityToManagedEntity[entity];
    _entityToManagedEntity[_managedEntities.back()] = index;
    _entityToManagedEntity.erase(entity);
    _managedEntities[index] = _managedEntities.back();
    _managedEntities.pop_back();
}

const std::vector<Entity> &AbstractSystem::getManagedEntities() const
{
    return _managedEntities;
}