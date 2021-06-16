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
        throw std::invalid_argument("Key " + key + " already exist");
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
    _entities.clear();
    _anonymousEntities.clear();
}

void Engine::EntityPack::removeEntity(const std::string &key)
{
    if (_entities.find(key) == _entities.end()) {
        throw std::invalid_argument("EntityPack:: removeEntity: Key not found");
    }
    _entityManager.removeEntity(_entities[key]);
    _entities.erase(key);
}

void Engine::EntityPack::removeEntity(const Engine::Entity entity)
{
    auto it = std::find(_anonymousEntities.begin(), _anonymousEntities.end(), entity);

    if (it == _anonymousEntities.end()) {
        throw std::invalid_argument("EntityPack:: removeEntity: Entity not found");
    }
    _entityManager.removeEntity(entity);
    _anonymousEntities.erase(it);
}
