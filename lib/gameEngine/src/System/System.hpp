/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 System.hpp.h
*/

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <cctype>
#include "EntityManager/EntityManager.hpp"
#include "env.hpp"

template <std::size_t ComponentCount, std::size_t SystemCount>
class EntityManager;

template <std::size_t ComponentCount, std::size_t SystemCount>
class System {
  public:
    System() : _type(0) {}
    virtual ~System() = default;

  protected:
    template <typename... Ts>
    void setRequirements()
    {
        (_requirements.set(Ts::type), ...);
    }

    const std::vector<Entity> &getManagedEntities() const
    {
        return _managedEntities;
    }

    virtual void onManagedEntityAdded(Entity entity) {}

    virtual void onManagedEntityRemoved(Entity entity) {}

  private:
    friend EntityManager<ComponentCount, SystemCount>;

    std::bitset<ComponentCount> _requirements;
    std::size_t _type;
    std::vector<Entity> _managedEntities;
    std::unordered_map<Entity, Index> _entityToManagedEntity;

    void setUp(std::size_t type)
    {
        _type = type;
    }

    void onEntityUpdated(Entity entity, const std::bitset<ComponentCount> &components)
    {
        bool satisfied = (_requirements & components) == _requirements;
        bool managed = _entityToManagedEntity.find(entity) != std::end(_entityToManagedEntity);

        if (satisfied && !managed) {
            this->addEntity(entity);
        } else if (!satisfied && managed) {
            this->removeEntity(entity);
        }
    }

    void onEntityRemoved(Entity entity)
    {
        if (_entityToManagedEntity.find(entity) != std::end(_entityToManagedEntity)) {
            this->removeEntity(entity);
        }
    }

    void addEntity(Entity entity)
    {
        _entityToManagedEntity[entity] = static_cast<Index>(_managedEntities.size());
        _managedEntities.emplace_back(entity);
        this->onManagedEntityAdded(entity);
    }

    void removeEntity(Entity entity)
    {
        this->onManagedEntityRemoved(entity);
        auto index = _entityToManagedEntity[entity];
        _entityToManagedEntity[_managedEntities.back()] = index;
        _entityToManagedEntity.erase(entity);
        _managedEntities[index] = _managedEntities.back();
        _managedEntities.pop_back();
    }
};

#endif // SYSTEM_HPP
