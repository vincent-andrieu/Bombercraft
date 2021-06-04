/*
 * EPITECH PROJECT, 2021
 * Hitbox
 * File description:
 * HitboxSystem.cpp - Created: 03/06/2021
 */

#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "Game/Core/Core.hpp"

System::HitboxSystem::HitboxSystem() : AbstractSystem(Game::Core::entityManager)
{
    this->setRequirements<Component::Hitbox>();
}

void System::HitboxSystem::update()
{
    for (const Engine::Entity &fromEntity : this->getManagedEntities())
        if (this->_entityManager.hasComponent<Engine::Velocity>(fromEntity)) {
            Component::Hitbox fromHitboxComp = this->_entityManager.getComponent<Component::Hitbox>(fromEntity);
            for (const Engine::Entity &toEntity : this->getManagedEntities())
                if (fromEntity != toEntity) {
                    Component::Hitbox toHitboxComp = this->_entityManager.getComponent<Component::Hitbox>(toEntity);
                    if (fromHitboxComp.objectBox.checkCollisionWith(toHitboxComp.objectBox)) {
                        fromHitboxComp.trigger(fromEntity, toEntity);
                        toHitboxComp.trigger(fromEntity, toEntity);
                    }
                }
        }
}