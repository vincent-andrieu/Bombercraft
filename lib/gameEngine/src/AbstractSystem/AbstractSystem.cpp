/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 31/05/2021 AbstractSystem.c
*/

#include "AbstractSystem.hpp"

using namespace Engine;

AbstractSystem::AbstractSystem(EntityManager &entityManager) : _entityManager(entityManager)
{
}

AbstractSystem::AbstractSystem(const AbstractSystem &src)
    : _entityManager(src._entityManager), _requirements(src._requirements), _managedEntities(src._managedEntities),
      _entityToManagedEntity(src._entityToManagedEntity)
{
}

void AbstractSystem::onEntityUpdated(Entity entity, const Signature &components)
{
    this->_mutex.lock();
    bool satisfied = (_requirements & components) == _requirements;
    bool managed = _entityToManagedEntity.find(entity) != std::end(_entityToManagedEntity);
    this->_mutex.unlock();

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
    std::lock_guard<std::mutex> lock_guard(this->_mutex);

    _entityToManagedEntity[entity] = static_cast<Index>(_managedEntities.size());
    _managedEntities.emplace_back(entity);
    this->onManagedEntityAdded(entity);
}

void AbstractSystem::removeEntity(Entity entity)
{
    std::lock_guard<std::mutex> lock_guard(this->_mutex);

    this->onManagedEntityRemoved(entity);
    auto index = _entityToManagedEntity[entity];
    _entityToManagedEntity[_managedEntities.back()] = index;
    _entityToManagedEntity.erase(entity);
    _managedEntities[index] = _managedEntities.back();
    _managedEntities.pop_back();
}

const std::vector<Entity> AbstractSystem::getManagedEntities()
{
    std::lock_guard<std::mutex> lock_guard(this->_mutex);

    return _managedEntities;
}