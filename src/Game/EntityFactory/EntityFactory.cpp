/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 07/06/2021 EntityFactory.cpp.cc
*/

#include "EntityFactory.hpp"

#include "Game/Factories/ButtonFactory.hpp"

using namespace Game;

const std::unordered_map<EntityType, Factory> EntityFactory::_factories {
    {EntityType::BUTTON, buttonFactory}
};

Engine::Entity EntityFactory::create(
    EntityType type, Engine::EntityPack &pack, IStaticFactoryData const &staticData, IDynFactoryData const &dynamicData)
{
    if (_factories.find(type) == _factories.end()) {
        throw std::invalid_argument("Not factory found for entityType type");
    }
    return _factories.at(type)(pack, staticData, dynamicData);
}
