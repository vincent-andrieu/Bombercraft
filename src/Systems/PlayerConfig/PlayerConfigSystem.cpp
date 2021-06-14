/*
 * EPITECH PROJECT, 2021
 * PlayerConfig
 * File description:
 * PlayerConfigSystem.cpp - Created: 11/06/2021
 */

#include "Systems/PlayerConfig/PlayerConfigSystem.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "Game/Core/Core.hpp"

System::PlayerConfigSystem::PlayerConfigSystem() : AbstractSystem(*Game::Core::entityManager)
{
    this->setRequirements<Component::PlayerConfig>();
}

/**
 * @brief Get player id config
 *
 * @param playerId
 * @return const Component::PlayerConfig&
 */
Component::PlayerConfig &System::PlayerConfigSystem::getPlayerFromID(const uint playerId) const
{
    for (const Engine::Entity &entity : this->getManagedEntities()) {
        Component::PlayerConfig &playerConfComp = this->_entityManager.getComponent<Component::PlayerConfig>(entity);
        if (playerConfComp.getPlayerId() == playerId)
            return playerConfComp;
    }
    throw std::out_of_range("invalid player id");
}

/**
 * @brief Get all player config
 *
 * @return const std::vector<const Component::PlayerConfig &>
 */
const std::vector<Component::PlayerConfig> System::PlayerConfigSystem::getPlayers() const
{
    std::vector<Component::PlayerConfig> playersConf;

    for (const Engine::Entity &entity : this->getManagedEntities()) {
        playersConf.push_back(this->_entityManager.getComponent<Component::PlayerConfig>(entity));
    }
    return playersConf;
}

/**
 * @brief Get next player config
 *
 * @param playerConfig
 * @return const Component::PlayerConfig&
 */
Component::PlayerConfig &System::PlayerConfigSystem::getNextPlayer(const Component::PlayerConfig &playerConfig) const
{
    const auto &entities = this->getManagedEntities();

    for (const Engine::Entity &entity : entities) {
        Component::PlayerConfig &entityComp = this->_entityManager.getComponent<Component::PlayerConfig>(entity);
        if (entityComp.getPlayerId() > playerConfig.getPlayerId())
            return entityComp;
    }
    return this->_entityManager.getComponent<Component::PlayerConfig>(entities.front());
}