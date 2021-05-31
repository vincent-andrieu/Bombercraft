/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 ComponentContainer.hpp.h
*/

#ifndef COMPONENTCONTAINER_HPP
#define COMPONENTCONTAINER_HPP

#include "IComponentContainer.hpp"

#include <vector>
#include <unordered_map>
#include <bitset>

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
class ComponentContainer : public IComponentContainer {
  public:
    ComponentContainer(std::vector<std::bitset<ComponentCount>> &entityToBitset);

    virtual void reserve(std::size_t size) override;

    T& get(Entity entity);

    template <typename... Args>
    void add(Entity entity, Args&&... args);
    void remove(Entity entity);
    virtual bool tryRemove(Entity entity) override;
    Entity getOwner(const T& component);

  private:
    std::vector<T> _components;
    std::vector<Entity> _componentToEntity;
    std::unordered_map<Entity, Index> _entityToComponent;
    std::vector<std::bitset<ComponentCount>> &_entityToBitset;
};

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
ComponentContainer<T, ComponentCount, SystemCount>::ComponentContainer(std::vector<std::bitset<ComponentCount>> &entityToBitset)
: _entityToBitset(entityToBitset)
{
}

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
void ComponentContainer<T, ComponentCount, SystemCount>::reserve(std::size_t size)
{
    _components.reserve(size);
    _componentToEntity.reserve(size);
    _entityToComponent.reserve(size);
}

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
T &ComponentContainer<T, ComponentCount, SystemCount>::get(Entity entity)
{
    return _components[_entityToComponent[entity]];
}

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
template <typename... Args>
void ComponentContainer<T, ComponentCount, SystemCount>::add(Entity entity, Args &&...args)
{
    auto index = static_cast<Index>(_components.size());

    _components.emplace_back(std::forward<Args>(args)...);
    _componentToEntity.emplace_back(entity);
    _entityToComponent[entity] = index;
    _entityToBitset[entity][T::type] = true;
}

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
void ComponentContainer<T, ComponentCount, SystemCount>::remove(Entity entity)
{
    _entityToBitset[entity][T::type] = false;
    auto index = _entityToComponent[entity];
    // update _components
    _components[index] = std::move(_components.back());
    _components.pop_back();
    // update _entityToComponent
    _entityToComponent[_componentToEntity.back()] = index;
    _entityToComponent.erase(entity);
    // update _componentToEntity
    _componentToEntity[index] = _componentToEntity.back();
    _componentToEntity.pop_back();
}

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
bool ComponentContainer<T, ComponentCount, SystemCount>::tryRemove(Entity entity)
{
    if (_entityToBitset[entity][T::type]) {
        this->remove(entity);
        return true;
    }
    return false;
}

template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
Entity ComponentContainer<T, ComponentCount, SystemCount>::getOwner(const T &component)
{
    auto begin = _components.data();
    auto index = static_cast<std::size_t>(&component - begin);
    return _componentToEntity[index];
}

#endif // COMPONENTCONTAINER_HPP
