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
#include "Game/Factories/Sound/AudioFactory.hpp"
#include "Game/Core/Core.hpp"

using namespace GUI;

extern std::unique_ptr<Game::Core> core;

static const Game::EventRequirement clickHandlerRequirements(Game::CLK_LEFT);

const raylib::MyVector2 ButtonFactory::SmallProportions(13, 8);
const raylib::MyVector2 ButtonFactory::MediumProportions(24.5, 8);
const raylib::MyVector2 ButtonFactory::BigProportions(33, 8);
const raylib::MyVector2 ButtonFactory::LargeProportions(50, 8);
const raylib::MyVector2 ButtonFactory::BigHighProportions(33, 16);

ButtonConfig ButtonFactory::getStandardButtonConfig(const raylib::MyVector2 &buttonSize)
{
    ButtonConfig my_standard{Game::CoreData::settings->getString("STANDARD_IDLE_BUTTON_TEXTURE"),
        Game::CoreData::settings->getString("STANDARD_HOVER_BUTTON_TEXTURE"),
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

ButtonConfig ButtonFactory::getBighHighButtonConfig()
{
    return getSizedButtonConfig(BigHighProportions);
}

ButtonConfig ButtonFactory::getLargeButtonConfig()
{
    return getSizedButtonConfig(LargeProportions);
}

Engine::Entity GUI::ButtonFactory::create(Engine::EntityPack &pack,
    const raylib::MyVector2 &position,
    const string &name,
    const GUI::ButtonConfig &conf,
    const string &label,
    const Component::eventScript clickAction,
    const bool centered)
{
    const auto &mySize(conf.size);
    auto myPosition((position));
    Engine::Entity entity;
    if (centered)
        myPosition = myPosition - ProportionUtilities::getProportionWin(mySize, raylib::MyVector2(50, 50));
    if (name.empty()) {
        throw std::invalid_argument("ButtonFactory::create empty entity name");
    } else {
        entity = pack.createEntity(name);
    }

    auto myLabel(std::make_shared<raylib::Text>(label,
        myPosition,
        conf.fontSize,
        conf.fontColor,
        std::shared_ptr<raylib::Font>(std::make_shared<raylib::Font>(conf.fontPath))));

    raylib::Text::setFontSize(*myLabel, (conf.size.a < 20 && conf.size.b < 20) ? conf.size : conf.size - 20);
    auto myLabelPosition(myPosition
        + ProportionUtilities::getProportionWin(
            mySize, raylib::MyVector2(50, 40), myLabel->getSize(), raylib::MyVector2(50, 40)));
    myLabel->setPosition(myLabelPosition);
    Component::render2dMapModels my_models({
        {"unavailable", std::make_shared<raylib::Texture>(conf.unavailableTexturePath, mySize, myPosition)},
        {"idle", std::make_shared<raylib::Texture>(conf.idleTexturePath, mySize, myPosition)},
        {"hover", std::make_shared<raylib::Texture>(conf.hoverTexturePath, mySize, myPosition)},
        {"label", myLabel},
    });

    Component::eventScript my_moveHandler = [myPosition, mySize](const Engine::Entity entity) {
        auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

        if (!my_render.isSetToDraw("unavailable")) {
            if (Game::CoreData::eventManager->MouseIsOver(myPosition, mySize)) {
                my_render.setToDrawFirst("hover");
                my_render.unsetToDraw("idle");
            } else {
                my_render.unsetToDraw("hover");
                my_render.setToDrawFirst("idle");
            }
        }
    };
    Component::eventScript my_clickHandler = [myPosition, mySize, clickAction](const Engine::Entity entity) {
        const auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

        if (Game::CoreData::eventManager->MouseIsOverClicked(myPosition, mySize) && !my_render.isSetToDraw("unavailable")) {
            Game::CoreData::systemManager->getSystem<System::AudioSystem>().play("ButtonClick", core->globalEntities);

            clickAction(entity);
        }
    };
    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(entity, my_clickHandler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, my_moveHandler);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, my_models);

    auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

    my_render.unsetToDraw("hover");
    my_render.unsetToDraw("unavailable");

    return entity;
}

Engine::Entity ButtonFactory::create(Engine::EntityPack &pack,
    const raylib::MyVector2 &position,
    ButtonConfig const &conf,
    const Component::eventScript clickAction,
    const string &screenPath,
    const string &label,
    bool centered,
    const string &name)
{
    auto mySize(conf.size);
    auto myPosition(centered ? position - ProportionUtilities::getProportionWin(mySize, raylib::MyVector2(50, 50)) : position);
    const Engine::Entity &entity = name.empty() ? pack.createAnonymousEntity() : pack.createEntity(name);
    const raylib::MyVector2 screenSize((mySize.a * 0.33f), mySize.b);

    // Label
    raylib::MyVector2 labelSize(mySize);
    auto myLabel(std::make_shared<raylib::Text>(label,
        myPosition,
        conf.fontSize,
        conf.fontColor,
        std::shared_ptr<raylib::Font>(std::make_shared<raylib::Font>(conf.fontPath))));
    labelSize.a -= screenSize.a;
    labelSize = (labelSize.a < 20 && labelSize.b < 20) ? labelSize : labelSize - 20;
    labelSize = labelSize * 0.85f;
    auto my_labelPosition(
        myPosition + raylib::MyVector2(screenSize.a, 0) + ProportionUtilities::getProportionWin(labelSize, {15, 15}));
    myLabel->setPosition(my_labelPosition);
    raylib::Text::setFontSize(*myLabel, labelSize);
    Component::render2dMapModels my_models({
        {"unavailable", std::make_shared<raylib::Texture>(conf.unavailableTexturePath, mySize, myPosition)},
        {"idle", std::make_shared<raylib::Texture>(conf.idleTexturePath, mySize, myPosition)},
        {"hover", std::make_shared<raylib::Texture>(conf.hoverTexturePath, mySize, myPosition)},
        {"label", myLabel},
    });

    // Button
    Component::eventScript my_moveHandler = [myPosition, mySize](const Engine::Entity entity) {
        auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

        if (!my_render.isSetToDraw("unavailable")) {
            if (Game::CoreData::eventManager->MouseIsOver(myPosition, mySize)) {
                my_render.setToDrawFirst("hover");
                my_render.unsetToDraw("idle");
            } else {
                my_render.unsetToDraw("hover");
                my_render.setToDrawFirst("idle");
            }
        }
    };
    Component::eventScript my_clickHandler = [myPosition, mySize, clickAction](const Engine::Entity entity) {
        const auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

        if (Game::CoreData::eventManager->MouseIsOverClicked(myPosition, mySize) && !my_render.isSetToDraw("unavailable")) {
            Game::CoreData::systemManager->getSystem<System::AudioSystem>().play("ButtonClick", core->globalEntities);

            clickAction(entity);
        }
    };
    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(entity, my_clickHandler, conf.requirements);
    Game::CoreData::entityManager->addComponent<Component::MouseMoveEvent>(entity, my_moveHandler);
    Game::CoreData::entityManager->addComponent<Component::Render2D>(entity, my_models);
    const raylib::MyVector2 buttonBorder((mySize.a * 0.6f) / 100, (mySize.b * 5) / 100);
    if (!screenPath.empty() && std::filesystem::exists(screenPath) && std::filesystem::is_regular_file(screenPath))
        GUI::ImageFactory::create(pack, myPosition + buttonBorder, screenSize - buttonBorder * 2, screenPath, true);

    auto &my_render(Game::CoreData::entityManager->getComponent<Component::Render2D>(entity));

    my_render.unsetToDraw("hover");
    my_render.unsetToDraw("unavailable");

    return entity;
}