/*
 * EPITECH PROJECT, 2021
 * Hitbox
 * File description:
 * HitboxSystem.cpp - Created: 03/06/2021
 */

#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "Game/Core/Core.hpp"

System::HitboxSystem::HitboxSystem() : AbstractSystem(*Game::Core::entityManager)
{
    this->setRequirements<Component::Hitbox>();
}

void System::HitboxSystem::update()
{
    for (const Engine::Entity &fromEntity : this->getManagedEntities()) {
        if (this->_entityManager.hasComponent<Engine::Velocity>(fromEntity)) {
            std::cout << "START 10" << std::endl;
            Component::Hitbox &fromHitboxComp = this->_entityManager.getComponent<Component::Hitbox>(fromEntity); // DEBUG
            std::cout << "END 10" << std::endl;
            for (const Engine::Entity &toEntity : this->getManagedEntities())
                if (fromEntity != toEntity) {
                    std::cout << "START 11" << std::endl;
                    Component::Hitbox &toHitboxComp = this->_entityManager.getComponent<Component::Hitbox>(toEntity);
                    std::cout << "END 11" << std::endl;
                    if (fromHitboxComp.objectBox->checkCollisionWith(*toHitboxComp.objectBox)) {
                        fromHitboxComp.trigger(fromEntity, toEntity);
                        toHitboxComp.trigger(fromEntity, toEntity);
                    }
                }
        }
    }
}