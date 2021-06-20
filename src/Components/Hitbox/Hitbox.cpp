/*
 * EPITECH PROJECT, 2021
 * Hitbox
 * File description:
 * Hitbox.cpp - Created: 03/06/2021
 */

#include "Hitbox.hpp"
#include "Game/CoreData/CoreData.hpp"

using namespace Component;

Hitbox::Hitbox(const raylib::MyVector3 &origin, const raylib::MyVector3 &size, hitboxHandler handler, Game::EntityType typeEntity)
    : objectBox(std::make_shared<ObjectBox>(origin, size)), entityType(typeEntity), _handler(handler),
      _debugRender(nullptr, origin, size)
{
}

void Hitbox::trigger(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    this->_handler(fromEntity, toEntity);
}

void Hitbox::debugRender()
{
    raylib::MyVector3 position = this->objectBox->getBoxOrigin();
    raylib::MyVector3 size = this->objectBox->getBoxSize();
    this->_debugRender.setPosition(position);
    this->_debugRender.setSize(size);
    Game::CoreData::camera->begin3D();
    this->_debugRender.draw();
    Game::CoreData::camera->end3D();
}