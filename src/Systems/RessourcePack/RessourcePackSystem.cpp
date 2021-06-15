/*
 * EPITECH PROJECT, 2021
 * RessourcePack
 * File description:
 * RessourcePackSystem.cpp - Created: 15/06/2021
 */

#include "RessourcePackSystem.hpp"
#include "Components/RessourcePack/RessourcePackComponent.hpp"

System::RessourcePackSystem::RessourcePackSystem() : AbstractSystem(*Game::CoreData::entityManager)
{
    this->setRequirements<Component::RessourcePack>();
}

void System::RessourcePackSystem::set(const string &ressourcePack)
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        Component::RessourcePack &component = this->_entityManager.getComponent<Component::RessourcePack>(entity);
        component.set(ressourcePack);
    }
}