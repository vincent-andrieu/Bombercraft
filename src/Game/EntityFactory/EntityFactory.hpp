/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 07/06/2021 EntityFactory.hpp.h
*/

#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"
#include <memory>
#include <unordered_map>
#include "IFactoryData.hpp"

namespace Game
{
    enum class EntityType
    {
        BUTTON
    };

    using Factory = std::function<Engine::Entity(Engine::EntityPack &pack, const IStaticFactoryData,
        const IDynFactoryData)>;

    class EntityFactory {
      public:
        EntityFactory() = delete;
        ~EntityFactory() = delete;

        static Engine::Entity create(Game::EntityType type, Engine::EntityPack &pack, const IStaticFactoryData &staticData,
            const IDynFactoryData &dynamicData);

      private:
        static const std::unordered_map<EntityType, Factory> _factories;
    };
} // namespace Game

#endif // ENTITYFACTORY_HPP
