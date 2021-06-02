/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityRegister.cpp.cc
*/

#include "EntityRegister.hpp"

using namespace Engine;

void EntityRegister::allocate(std::size_t size)
{
    _freeEntities.resize(size);
    std::iota(std::begin(_freeEntities), std::end(_freeEntities), 0);
    _entitySignatures.resize(size);
}

std::vector<Signature> &EntityRegister::getEntitySignatures()
{
    return _entitySignatures;
}

const Signature &EntityRegister::getSignature(Entity entity) const
{
    return _entitySignatures[entity];
}

Entity EntityRegister::create()
{
    Entity entity = 0;

    if (_freeEntities.empty()) {
        entity = static_cast<Entity>(_entitySignatures.size());
        _entitySignatures.emplace_back();
    } else {
        entity = _freeEntities.back();
        _freeEntities.pop_back();
        _entitySignatures[entity].reset();
    }
    return entity;
}

void EntityRegister::remove(Entity entity)
{
    _freeEntities.push_back(entity);
}
