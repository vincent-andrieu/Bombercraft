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

    if (key.empty()) {
        throw std::invalid_argument("EntityPack::createEntity Empty key are forbidden.");
    }
    if (_entities.find(key) != _entities.end()) {
        throw std::invalid_argument("EntityPack::createEntity Key " + key + " already exists");
    }
    entity = _entityManager.createEntity();
    _entities[key] = entity;
    return entity;
}

Engine::Entity Engine::EntityPack::getEntity(const std::string &key)
{
    if (_entities.find(key) == _entities.end()) {
        throw std::invalid_argument("EntityPack::getEntity Key (" + key + ") not found");
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

void Engine::EntityPack::removeEntity(const std::string key)
{
    if (_entities.find(key) == _entities.end()) {
        throw std::invalid_argument("EntityPack:: removeEntity: Key " + key + " not found");
    }
    _entityManager.removeEntity(_entities[key]);
    _entities.erase(key);
}

bool Engine::EntityPack::entityIsSet(const std::string &key)
{
    if (_entities.find(key) == _entities.end())
        return false;
    return true;
}

void Engine::EntityPack::removeEntity(const Engine::Entity entity)
{
    auto it = std::find(_anonymousEntities.begin(), _anonymousEntities.end(), entity);

    if (it == _anonymousEntities.end()) {
        auto itKey = std::find_if(_entities.begin(), _entities.end(), [entity](auto &pair) {
            return pair.second == entity;
        });
        if (itKey == _entities.end()) {
            throw std::invalid_argument("EntityPack:: removeEntity: Entity not found");
        } else {
            this->removeEntity(itKey->first);
        }
    } else {
        _entityManager.removeEntity(entity);
        _anonymousEntities.erase(it);
    }
}