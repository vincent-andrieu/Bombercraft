/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 ButtonEntity.cpp.cc
*/

#include "ButtonFactory.hpp"

using namespace GUI;

ButtonConfig ButtonFactory::standardButton()
{
    ButtonConfig my_standard{Game::CoreData::settings->getString("STANDARD_IDLE_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_CLICKED_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"),
        {10, 10},
        static_cast<size_t>(Game::CoreData::settings->getInt("STANDARD_FONT_SIZE")),
        raylib::RColor::RWHITE,
        Game::CoreData::settings->getString("STANDARD_FONT"),
        Game::EventRequirement(Game::evtMouse::LEFT)};
    return my_standard;
}

void GUI::ButtonFactory::create(Engine::EntityPack &pack,
    raylib::MyVector2 &position,
    const string &label,
    Component::eventScript &handler,
    const GUI::ButtonConfig &conf)
{
    Engine::Entity entity = pack.createAnonymousEntity();
    Component::render2dMapModels my_models({{label, std::make_shared<raylib::Rectangle>(position, conf.size)}});

    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(entity, handler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, handler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, my_models);
}