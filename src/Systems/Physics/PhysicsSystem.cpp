/*
 * EPITECH PROJECT, 2021
 * Physic
 * File description:
 * PhysicsSystem.cpp - Created: 10/06/2021
 */

#include "PhysicsSystem.hpp"

System::PhysicsSystem::PhysicsSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::Render3D, Engine::Velocity>();
}

void System::PhysicsSystem::update(float dt)
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto [render, velocity] = this->_entityManager.getComponents<Component::Render3D, Engine::Velocity>(entity);
        const raylib::MyVector3 &position = render.modele->getPosition() + raylib::MyVector3(velocity.x * dt, velocity.y * dt);
        render.modele->setPosition(position);
        if (this->_entityManager.hasComponent<Component::Hitbox>(entity)) {
            Component::Hitbox &hitboxComponent = this->_entityManager.getComponent<Component::Hitbox>(entity);
            hitboxComponent.objectBox->setOrigin(position);
        }
    }
}