/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** LabelFactory
*/

#include "LabelFactory.hpp"

using namespace GUI;

void LabelFactory::create(Engine::EntityPack &pack, raylib::MyVector2 position, std::string const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"text", std::make_shared<raylib::Text>(label, position, config.fontSize, config.fontColor, config.fontPath)}
    }));
}

void LabelFactory::create(Engine::EntityPack &pack, raylib::MyVector2 position, std::size_t const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"text", std::make_shared<raylib::Text>(std::to_string(label), position, config.fontSize, config.fontColor, config.fontPath)}
    }));
}

void LabelFactory::create(Engine::EntityPack &pack, raylib::MyVector2 position, int const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"text", std::make_shared<raylib::Text>(std::to_string(label), position, config.fontSize, config.fontColor, config.fontPath)}
    }));
}

void LabelFactory::create(Engine::EntityPack &pack, raylib::MyVector2 position, float const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({
            {"text", std::make_shared<raylib::Text>(std::to_string(label), position, config.fontSize, config.fontColor, config.fontPath)}
    }));
}