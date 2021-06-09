/*
 * EPITECH PROJECT, 2021
 * Checkbox
 * File description:
 * CheckboxEntity.cpp - Created: 07/06/2021
 */

#include "CheckboxFactory.hpp"
#include "Components/Render2D/Render2D.hpp"

using namespace raylib;
using namespace GUI;
using namespace Game;

const EventRequirement CheckboxFactory::_clickHandlerRequirements(evtMouse::LEFT | evtMouse::RIGHT);

void CheckboxFactory::create(
    Engine::EntityPack &entityPack, const MyVector2 position, checkboxHandler clickHandler, bool isDefaultChecked)
{
    const auto checkbox = entityPack.createAnonymousEntity();
    const auto &size = CoreData::settings->getMyVector2(CHECKBOX_CONFIG_SIZE);
    const auto &outlineSize = CoreData::settings->getMyVector2(CHECKBOX_CONFIG_OUTLINE);
    auto backgroundRect = std::make_shared<raylib::Rectangle>(
        position, size, static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_OUTLINE_COLOR)));
    auto checkRect = std::make_shared<raylib::Rectangle>(position + outlineSize, size - 2 * outlineSize,
        static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_DISABLE_COLOR)));

    Component::eventScript checkboxHandler = [checkRect, isDefaultChecked, clickHandler, position, size](
                                                 const Engine::Entity entity) {
        static bool isChecked = isDefaultChecked;

        if (CoreData::eventManager->MouseIsOverClicked(position, size)) {
            isChecked = !isChecked;
            checkRect->setColor(CheckboxFactory::getCheckColor(isChecked));
            clickHandler(entity, isChecked);
        }
    };

    CoreData::entityManager->addComponent<Component::Render2D>(
        checkbox, Component::render2dMapModels{{"checkboxCheck", checkRect}, {"checkboxBackground", backgroundRect}});
    CoreData::entityManager->addComponent<Component::ClickEvent>(
        checkbox, checkboxHandler, CheckboxFactory::_clickHandlerRequirements);
}

RColor CheckboxFactory::getCheckColor(bool isChecked)
{
    if (isChecked)
        return static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_ENABLE_COLOR));
    return static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_DISABLE_COLOR));
}