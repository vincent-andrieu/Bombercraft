/*
 * EPITECH PROJECT, 2021
 * Hitbox
 * File description:
 * Hitbox.cpp - Created: 03/06/2021
 */

#include "Hitbox.hpp"

using namespace Component;

Hitbox::Hitbox(const MyVector3 origin, const MyVector3 size, hitboxHandler &handler, Engine::SceneManager &sceneManager)
    : objectBox(origin, size), _handler(handler), _sceneManager(sceneManager)
{
}

void Hitbox::trigger(Engine::EntityManager &entityManager, const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    this->_handler(entityManager, this->_sceneManager, fromEntity, toEntity);
}