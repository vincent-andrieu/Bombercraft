/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** LabelFactory
*/

#include "LabelFactory.hpp"
#include "Utilities/ProportionUtilities.hpp"

using namespace GUI;

LabelConfig LabelFactory::getStandardLabelConfig(const std::size_t fontSize)
{
    return {fontSize, raylib::RColor::RWHITE, Game::CoreData::settings->getString("STANDARD_FONT")};
}

void LabelFactory::create(Engine::EntityPack &pack, raylib::MyVector2 position, string const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels(
            {{"text", std::make_shared<raylib::Text>(label, config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::create(
    Engine::EntityPack &pack, raylib::MyVector2 position, std::size_t const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({{"text",
            std::make_shared<raylib::Text>(toString(label), config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::create(Engine::EntityPack &pack, raylib::MyVector2 position, int const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({{"text",
            std::make_shared<raylib::Text>(toString(label), config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::create(Engine::EntityPack &pack, raylib::MyVector2 position, float const &label, LabelConfig const &config)
{
    Engine::Entity entity = pack.createAnonymousEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels({{"text",
            std::make_shared<raylib::Text>(toString(label), config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::createCentered(
    Engine::EntityPack &pack, raylib::MyVector2 position, string const &label, LabelConfig const &config)
{
    auto my_text(std::make_shared<raylib::Text>(label, config.fontPath, position, config.fontSize, config.fontColor));
    Engine::Entity entity = pack.createAnonymousEntity();
    const auto my_position(position - ProportionUtilities::getProportionWin(my_text->getSize(), raylib::MyVector2(50, 50)));

    my_text->setPosition(my_position);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, Component::render2dMapModels({{"text", my_text}}));
}