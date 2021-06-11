/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 ButtonEntity.cpp.cc
*/

#include "ButtonFactory.hpp"

using namespace GUI;

static const Game::EventRequirement clickHandlerRequirements(Game::CLK_LEFT);

ButtonConfig ButtonFactory::getStandardButtonConfig(const raylib::MyVector2 &buttonSize)
{
    ButtonConfig my_standard{
        Game::CoreData::settings->getString("STANDARD_IDLE_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_CLICKED_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"),
        buttonSize,
        static_cast<size_t>(Game::CoreData::settings->getInt("STANDARD_FONT_SIZE")),
        raylib::RColor::RWHITE,
        Game::CoreData::settings->getString("STANDARD_FONT"),
        clickHandlerRequirements,
    };
    return my_standard;
}

// static const std::shared_ptr<raylib::Font> my_font(std::make_shared<raylib::Font>("conf.fontPath"));

void GUI::ButtonFactory::create(Engine::EntityPack &pack,
    const raylib::MyVector2 &position,
    const string &label,
    const GUI::ButtonConfig &conf,
    const std::string &text, // TODO add click action, event script that would be captured in clickHandler and execute on click
    const Component::eventScript &clickAction)
{
    const raylib::MyVector2 &my_position(position);
    raylib::MyVector2 my_size(conf.size);
    Engine::Entity entity = pack.createEntity(label);
    Component::render2dMapModels my_models(
        {{"text",
             std::make_shared<raylib::Text>(text,
                 my_position,
                 conf.fontSize,
                 conf.fontColor,
                 std::shared_ptr<raylib::Font>(std::make_shared<raylib::Font>(conf.fontPath)))},
            {"idle", std::make_shared<raylib::Texture>(conf.idleTexturePath, my_size, my_position)},
            {"hover", std::make_shared<raylib::Texture>(conf.hoverTexturePath, my_size, my_position)},
            {"clicked", std::make_shared<raylib::Texture>(conf.clickedTexturePath, my_size, my_position)},
            {"unavailable", std::make_shared<raylib::Texture>(conf.unavailableTexturePath, my_size, my_position)}});
    Component::eventScript my_moveHandler = [position, my_size](const Engine::Entity entity) {
        auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

        if (Game::CoreData::eventManager->MouseIsOver(position, my_size)) {
            my_render.unsetToDraw("idle");
            my_render.setToDrawFirst("hover");
        } else {
            my_render.unsetToDraw("hover");
            my_render.setToDrawFirst("idle");
        }
    };
    Component::eventScript my_clickHandler = [position, my_size, clickAction](const Engine::Entity entity) {
        auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));
        if (Game::CoreData::eventManager->MouseIsOverClicked(position, my_size)) {
            clickAction(entity);
        }
    };
    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(entity, my_clickHandler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, my_moveHandler);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, my_models);
    auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

    my_render.unsetToDraw("hover");
    my_render.unsetToDraw("clicked");
    my_render.unsetToDraw("unavailable");
}