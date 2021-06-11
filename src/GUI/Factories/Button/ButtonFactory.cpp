/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 ButtonEntity.cpp.cc
*/

#include "ButtonFactory.hpp"

using namespace GUI;

static const Game::EventRequirement clickHandlerRequirements(Game::evtMouse::LEFT);

ButtonConfig ButtonFactory::getStandardButtonConfig()
{
    ButtonConfig my_standard{
        Game::CoreData::settings->getString("STANDARD_IDLE_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_CLICKED_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"),
        {180, 20},
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
    const string &name,
    const GUI::ButtonConfig &conf,
    const string &label, // TODO add click action, event script that would be captured in clickHandler and execute on click
    const Component::eventScript &clickAction)
{
    raylib::MyVector2 my_position(position);
    raylib::MyVector2 my_size(conf.size);
    Engine::Entity entity = pack.createEntity(name);
    Component::render2dMapModels my_textureModels(
        {{"idle", std::make_shared<raylib::Texture>(conf.idleTexturePath, my_size, my_position)},
            {"hover", std::make_shared<raylib::Texture>(conf.hoverTexturePath, my_size, my_position)},
            {"clicked", std::make_shared<raylib::Texture>(conf.clickedTexturePath, my_size, my_position)},
            {"unavailable", std::make_shared<raylib::Texture>(conf.unavailableTexturePath, my_size, my_position)}});
    Component::render2dMapModels my_textModel({{"label",
        std::make_shared<raylib::Text>(label,
            my_position,
            conf.fontSize,
            conf.fontColor,
            std::shared_ptr<raylib::Font>(std::make_shared<raylib::Font>(conf.fontPath)))}});
    Component::eventScript my_moveHandler = [position, my_size](const Engine::Entity entity) {
        auto &my_render(Game::CoreData::entityManager->getComponent<Component::SingleRender2D>(entity));

        if (Game::CoreData::eventManager->MouseIsOver(position, my_size)) {
            my_render.setActRender2D("hover");
        } else {
            my_render.setActRender2D("idle");
        }
    };
    Component::eventScript my_clickHandler = [position, my_size, clickAction](const Engine::Entity entity) {
        auto &my_render(Game::CoreData::entityManager->getComponent<Component::SingleRender2D>(entity));

        if (Game::CoreData::eventManager->MouseIsOverClicked(position, my_size)) {
            //            my_render.setActRender2D("clicked"); // TODO have click texture ?
            my_render.setActRender2D("hover");
            clickAction(entity);
        } else {
            my_render.setActRender2D("idle");
        }
    };
    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(entity, my_clickHandler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, my_moveHandler);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, my_textModel);
    Game::CoreData::entityManager->addComponent<Component::SingleRender2D>(entity, my_textureModels);
}