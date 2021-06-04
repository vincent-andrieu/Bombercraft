/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** AbstractScene
*/

#include "AbstractScene.hpp"

using namespace Engine;

AbstractScene::AbstractScene(SystemManager &systemManager, EntityManager &entityManager)
    : localEntities(entityManager), _systemManager(systemManager), _entityManager(entityManager)
{
}

