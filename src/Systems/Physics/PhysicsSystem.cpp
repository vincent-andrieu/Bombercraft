/*
 * EPITECH PROJECT, 2021
 * Physic
 * File description:
 * PhysicsSystem.cpp - Created: 10/06/2021
 */

#include "PhysicsSystem.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/ModelList/ModelList.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "raylib.hpp"

System::PhysicsSystem::PhysicsSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::ModelList, Engine::Velocity>();
}

void System::PhysicsSystem::update(float dt)
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        auto [render, velocity] = this->_entityManager.getComponents<Component::ModelList, Engine::Velocity>(entity);
        const raylib::MyVector3 &position = render.getPosition() + raylib::MyVector3(velocity.x * dt, 0, velocity.y * dt);
        render.setPosition(position);
        if (this->_entityManager.hasComponent<Component::Hitbox>(entity)) {
            Component::Hitbox &hitboxComponent = this->_entityManager.getComponent<Component::Hitbox>(entity);
            const raylib::MyVector3 &oldPosition = hitboxComponent.objectBox->getBoxOrigin();
            hitboxComponent.objectBox->setOrigin(raylib::MyVector3({position.a, oldPosition.b, position.c}));
        }
    }
}