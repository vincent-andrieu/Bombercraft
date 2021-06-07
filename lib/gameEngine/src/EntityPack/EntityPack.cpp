/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 EntityPack.cpp.cc
*/

#include "EntityPack.hpp"

Engine::EntityPack::EntityPack(Engine::EntityManager &entityManager) : _entityManager(entityManager)
{
}

Engine::EntityPack::~EntityPack()
{
    this->unload();
}

Engine::Entity Engine::EntityPack::createEntity(const std::string &key)
{
    Entity entity;

    if (_entities.find(key) != _entities.end()) {
        throw std::invalid_argument("Key already exist");
    }
    entity = _entityManager.createEntity();
    _entities[key] = entity;
    return entity;
}

Engine::Entity Engine::EntityPack::getEntity(const std::string &key)
{
    if (_entities.find(key) == _entities.end()) {
        throw std::invalid_argument("Key not found");
    }
    return _entities[key];
}

Engine::Entity Engine::EntityPack::createAnonymousEntity()
{
    Entity e = _entityManager.createEntity();

    _anonymousEntities.push_back(e);
    return e;
}

void Engine::EntityPack::unload()
{
    for (auto [key, entity] : _entities) {
        _entityManager.removeEntity(entity);
    }
    for (Entity e : _anonymousEntities) {
        _entityManager.removeEntity(e);
    }
}