/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 ButtonEntity.cpp.cc
*/

#include "ButtonFactory.hpp"

using namespace GUI;

static const Game::EventRequirement clickHandlerRequirements(Game::evtMouse::LEFT);

namespace GUI
{
    void standardButtonHandler(const Engine::Entity entity) // TODO make one handler for click and one for move
    {
        Component::SingleRender2D my_render2D(Game::CoreData::entityManager->getComponent<Component::SingleRender2D>(entity));
        std::cout << "lol" << std::endl;
        my_render2D.setActRender2D("hover");
    }
} // namespace GUI

ButtonConfig ButtonFactory::getStandardButtonConfig()
{
    ButtonConfig my_standard{Game::CoreData::settings->getString("STANDARD_IDLE_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_CLICKED_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"),
        {10, 10},
        static_cast<size_t>(Game::CoreData::settings->getInt("STANDARD_FONT_SIZE")),
        raylib::RColor::RWHITE,
        Game::CoreData::settings->getString("STANDARD_FONT"),
        clickHandlerRequirements,
        standardButtonHandler,
        standardButtonHandler};
    return my_standard;
}

void GUI::ButtonFactory::create(Engine::EntityPack &pack,
    const raylib::MyVector2 &position,
    const string &label,
    const GUI::ButtonConfig &conf,
    const std::string &text)
{
    raylib::MyVector2 my_position(position);
    Engine::Entity entity = pack.createEntity(label);
    Component::render2dMapModels my_textureModels(
        {{"idle", std::make_shared<raylib::Texture>(conf.idleTexturePath, conf.size, my_position)},
            {"hover", std::make_shared<raylib::Texture>(conf.hoverTexturePath, conf.size, my_position)},
            {"clicked", std::make_shared<raylib::Texture>(conf.clickedTexturePath, conf.size, my_position)},
            {"unavailable", std::make_shared<raylib::Texture>(conf.unavailableTexturePath, conf.size, my_position)}});
    Component::render2dMapModels my_textModel({{"text",
        std::make_shared<raylib::Text>(
            text, my_position, conf.fontSize, conf.fontColor, std::make_shared<raylib::Font>(conf.fontPath))}});
    Component::eventScript my_clickHandler(conf.clickHandler);
    Component::eventScript my_moveHandler(conf.moveHandler);

    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(entity, my_clickHandler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, my_moveHandler);
    Game::CoreData::entityManager->addComponent<Component::SingleRender2D>(entity, my_textureModels);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, my_textModel);
}