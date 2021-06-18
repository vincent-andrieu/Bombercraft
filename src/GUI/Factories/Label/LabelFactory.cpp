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
            std::make_shared<raylib::Text>(
                toString(static_cast<std::size_t>(label * 10)), config.fontPath, position, config.fontSize, config.fontColor)}}));
}

void LabelFactory::create(Engine::EntityPack &pack,
    const raylib::MyVector2 position,
    const raylib::MyVector2 size,
    string const &label,
    LabelConfig const &config,
    const std::string &name,
    const bool centered)
{
    Engine::Entity entity;
    auto my_text(std::make_shared<raylib::Text>(label, config.fontPath, position, config.fontSize, config.fontColor));

    if (centered)
        raylib::Text::setFontSize(*my_text, size);
    my_text->setPosition(position
        + ProportionUtilities::getProportionWin(size, raylib::MyVector2(50, 50), my_text->getSize(), raylib::MyVector2(50, 50)));
    if (name.empty()) {
        entity = pack.createAnonymousEntity();
    } else {
        entity = pack.createEntity(name);
    }
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, Component::render2dMapModels({{"text", my_text}}));
}

Engine::Entity LabelFactory::createCentered(
    Engine::EntityPack &pack, raylib::MyVector2 position, string const &label, LabelConfig const &config, const std::string &name)
{
    Engine::Entity entity;
    auto my_text(std::make_shared<raylib::Text>(label, config.fontPath, position, config.fontSize, config.fontColor));
    const auto my_position(position - ProportionUtilities::getProportionWin(my_text->getSize(), raylib::MyVector2(50, 50)));

    if (name.empty()) {
        entity = pack.createAnonymousEntity();
    } else {
        entity = pack.createEntity(name);
    }
    my_text->setPosition(my_position);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, Component::render2dMapModels({{"text", my_text}}));

    return entity;
}

Engine::Entity LabelFactory::createCentered(Engine::EntityPack &pack,
    raylib::MyVector2 position,
    const raylib::MyVector2 size,
    string const &label,
    LabelConfig const &config,
    const std::string &name)
{
    Engine::Entity entity;
    auto my_text(std::make_shared<raylib::Text>(label, config.fontPath, position, 0, config.fontColor));
    raylib::Text::setFontSize(*my_text, size);
    const auto my_position(position - ProportionUtilities::getProportionWin(my_text->getSize(), raylib::MyVector2(50, 50)));

    if (name.empty()) {
        entity = pack.createAnonymousEntity();
    } else {
        entity = pack.createEntity(name);
    }
    my_text->setPosition(my_position);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, Component::render2dMapModels({{"text", my_text}}));

    return entity;
}