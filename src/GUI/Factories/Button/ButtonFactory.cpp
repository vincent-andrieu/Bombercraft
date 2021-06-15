/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 ButtonEntity.cpp.cc
*/

#include "ButtonFactory.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"

using namespace GUI;

static const Game::EventRequirement clickHandlerRequirements(Game::CLK_LEFT);

const raylib::MyVector2 ButtonFactory::SmallProportions(13, 8);
const raylib::MyVector2 ButtonFactory::MediumProportions(24.5, 8);
const raylib::MyVector2 ButtonFactory::BigProportions(33, 8);
const raylib::MyVector2 ButtonFactory::LargeProportions(50, 8);

ButtonConfig ButtonFactory::getStandardButtonConfig(const raylib::MyVector2 &buttonSize)
{
    ButtonConfig my_standard{Game::CoreData::settings->getString("STANDARD_IDLE_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_CLICKED_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_UNAVAILABLE_BUTTON_TEXTURE"),
        buttonSize,
        static_cast<size_t>(Game::CoreData::settings->getInt("STANDARD_FONT_SIZE")),
        raylib::RColor::RWHITE,
        Game::CoreData::settings->getString("STANDARD_FONT"),
        clickHandlerRequirements};
    return my_standard;
}

ButtonConfig ButtonFactory::getSizedButtonConfig(const raylib::MyVector2 &winPercent)
{
    static const auto &my_winSize(Game::CoreData::settings->getMyVector2("WIN_SIZE"));

    return getStandardButtonConfig(ProportionUtilities::getProportionWin(my_winSize, winPercent));
}

ButtonConfig ButtonFactory::getSmallButtonConfig()
{
    return getSizedButtonConfig(SmallProportions);
}

ButtonConfig ButtonFactory::getMediumButtonConfig()
{
    return getSizedButtonConfig(MediumProportions);
}

ButtonConfig ButtonFactory::getBigButtonConfig()
{
    return getSizedButtonConfig(BigProportions);
}

ButtonConfig ButtonFactory::getLargeButtonConfig()
{
    return getSizedButtonConfig(LargeProportions);
}

void GUI::ButtonFactory::create(Engine::EntityPack &pack,
    const raylib::MyVector2 &position,
    const string &name,
    const GUI::ButtonConfig &conf,
    const string &label, // TODO add click action, event script that would be captured in clickHandler and execute on click
    const Component::eventScript clickAction,
    const bool centered)
{
    const auto &my_size(conf.size);
    auto my_position((position));
    if (centered)
        my_position = my_position - ProportionUtilities::getProportionWin(my_size, raylib::MyVector2(50, 50));
    const auto entity = pack.createEntity(name);

    auto my_label(std::make_shared<raylib::Text>(label,
        my_position,
        conf.fontSize,
        conf.fontColor,
        std::shared_ptr<raylib::Font>(std::make_shared<raylib::Font>(conf.fontPath))));

    raylib::Text::setFontSize(*my_label, conf.size - 20);
    auto my_labelPosition(my_position + ProportionUtilities::getProportionWin(my_size, {50, 50}, my_label->getSize(), {50, 50}));
    my_label->setPosition(my_labelPosition);
    Component::render2dMapModels my_models({
        {"idle", std::make_shared<raylib::Texture>(conf.idleTexturePath, my_size, my_position)},
        {"hover", std::make_shared<raylib::Texture>(conf.hoverTexturePath, my_size, my_position)},
        {"label", my_label},
        /*{"clicked", std::make_shared<raylib::Texture>(conf.clickedTexturePath, my_size, my_position)},*/
        /*{"unavailable", std::make_shared<raylib::Texture>(conf.unavailableTexturePath, my_size, my_position)}*/});

    Component::eventScript my_moveHandler = [my_position, my_size](const Engine::Entity entity) {
        auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

        if (Game::CoreData::eventManager->MouseIsOver(my_position, my_size)) {
            my_render.setToDrawFirst("hover");
            my_render.unsetToDraw("idle");
        } else {
            my_render.unsetToDraw("hover");
            my_render.setToDrawFirst("idle");
        }
    };
    Component::eventScript my_clickHandler = [my_position, my_size, clickAction](const Engine::Entity entity) {
        if (Game::CoreData::eventManager->MouseIsOverClicked(my_position, my_size)) {
            clickAction(entity);
        }
    };
    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(entity, my_clickHandler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, my_moveHandler);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, my_models);
    auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

    my_render.unsetToDraw("hover");
    //    my_render.unsetToDraw("clicked");
    //    my_render.unsetToDraw("unavailable");
}