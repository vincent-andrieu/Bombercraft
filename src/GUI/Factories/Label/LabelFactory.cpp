/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** LabelFactory
*/

#include "LabelFactory.hpp"

using namespace GUI;

void LabelFactory::create(
    Engine::EntityPack &pack, raylib::MyVector2 position, string const &label, LabelConfig const &config, const std::string &name)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = pack.createAnonymousEntity();
    } else {
        entity = pack.createEntity(name);
    }
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels(
            {{"text", std::make_shared<raylib::Text>(label, config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::create(Engine::EntityPack &pack,
    raylib::MyVector2 position,
    std::size_t const &label,
    LabelConfig const &config,
    const std::string &name)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = pack.createAnonymousEntity();
    } else {
        entity = pack.createEntity(name);
    }
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({{"text",
            std::make_shared<raylib::Text>(toString(label), config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::create(
    Engine::EntityPack &pack, raylib::MyVector2 position, int const &label, LabelConfig const &config, const std::string &name)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = pack.createAnonymousEntity();
    } else {
        entity = pack.createEntity(name);
    }
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({{"text",
            std::make_shared<raylib::Text>(toString(label), config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::create(
    Engine::EntityPack &pack, raylib::MyVector2 position, float const &label, LabelConfig const &config, const std::string &name)
{
    Engine::Entity entity;

    if (name.empty()) {
        entity = pack.createAnonymousEntity();
    } else {
        entity = pack.createEntity(name);
    }
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({{"text",
            std::make_shared<raylib::Text>(toString(label), config.fontPath, position, config.fontSize, config.fontColor)}}));
}