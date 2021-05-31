/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityContainer.cpp.cc
*/

#include "EntityContainer.hpp"

void EntityContainer::reserve(std::size_t size)
{
    _freeEntities.resize(size);
    std::iota(std::begin(_freeEntities), std::end(_freeEntities), 0);
    _entityToBitset.resize(size);
}

std::vector<std::bitset<MAX_COMPONENT>> &EntityContainer::getEntityToBitset()
{
    return _entityToBitset;
}

const std::bitset<MAX_COMPONENT> &EntityContainer::getBitset(Entity entity) const
{
    return _entityToBitset[entity];
}

Entity EntityContainer::create()
{
    auto entity = Entity();

    if (_freeEntities.empty()) {
        entity = static_cast<Entity>(_entityToBitset.size());
        _entityToBitset.emplace_back();
    } else {
        entity = _freeEntities.back();
        _freeEntities.pop_back();
        _entityToBitset[entity].reset();
    }
    return entity;
}

void EntityContainer::remove(Entity entity)
{
    _freeEntities.push_back(entity);
}
