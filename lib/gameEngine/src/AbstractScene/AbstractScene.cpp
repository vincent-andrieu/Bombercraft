/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#include "AbstractScene.hpp"

using namespace Engine;

AbstractScene::AbstractScene(SystemManager &systemManager, EntityManager &entityManager)
    : _systemManager(systemManager), _entityManager(entityManager)
{
}

AbstractScene::~AbstractScene()
{
    while (false == _localEntities.empty()) {
        Entity entity = _localEntities.back();

        _entityManager.removeEntity(entity);
        _localEntities.pop_back();
    }
}

Entity AbstractScene::createLocalEntity()
{
    Entity entity = _entityManager.createEntity();

    _localEntities.push_back(entity);
    return entity;
}
