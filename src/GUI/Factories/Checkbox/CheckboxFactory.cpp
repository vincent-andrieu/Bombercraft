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
    Engine::EntityPack &entityPack, const MyVector2 position, Component::eventScript clickHandler, bool isDefaultChecked)
{
    const auto checkbox = entityPack.createEntity("checkbox");
    const auto &size = CoreData::settings->getMyVector2(CHECKBOX_CONFIG_SIZE);
    const auto &outlineSize = CoreData::settings->getMyVector2(CHECKBOX_CONFIG_OUTLINE);
    auto backgroundRect = std::make_shared<raylib::Rectangle>(
        position, size, static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_OUTLINE_COLOR)));
    auto checkRect = std::make_shared<raylib::Rectangle>(position + outlineSize, size - 2 * outlineSize,
        static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_DISABLE_COLOR)));

    Component::eventScript checkboxHandler = [checkRect, isDefaultChecked, clickHandler](const Engine::Entity entity) {
        static bool isChecked = isDefaultChecked;

        isChecked = !isChecked;
        checkRect->setColor(CheckboxFactory::getCheckColor(isChecked));
        clickHandler(entity);
    };

    CoreData::entityManager->addComponent<Component::Render2D>(
        checkbox, Component::render2dMapModels{{"checkboxBackground", backgroundRect}, {"checkboxCheck", checkRect}});
    CoreData::entityManager->addComponent<Component::ClickEvent>(
        checkbox, checkboxHandler, CheckboxFactory::_clickHandlerRequirements);
}

RColor CheckboxFactory::getCheckColor(bool isChecked)
{
    if (isChecked)
        return static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_ENABLE_COLOR));
    return static_cast<RColor>(CoreData::settings->getInt(CHECKBOX_CONFIG_DISABLE_COLOR));
}

// CheckboxFactory::CheckboxFactory(Engine::SystemManager &systemManager, const MyVector2 position, const MyVector2 size,
//     const MyVector2 outlineSize, const RColor outlineColor, const RColor enableColor, const RColor disableColor)
//     : _outlineSize(outlineSize), _enableColor(enableColor), _disableColor(disableColor),
//       _backgroundRect(std::make_shared<raylib::Rectangle>(position, size, outlineColor)),
//       _checkRect(std::make_shared<raylib::Rectangle>(position + outlineSize, size - 2 * outlineSize, disableColor))
// {
//     // auto checkbox = this->_entityPack.createEntity("checkbox");
//     auto checkbox = Game::CoreData::entityManager->createEntity();

//     Game::CoreData::entityManager->addComponent<Component::Render2D>(
//         checkbox, Component::render2dMapModels{{"background", this->_backgroundRect}, {"check", this->_checkRect}});
//     Game::CoreData::entityManager->addComponent<Component::ClickEvent>(
//         checkbox, CheckboxFactory::_clickHandler, this->_clickHandlerRequirements);
// }

// void CheckboxFactory::setPosition(const MyVector2 position)
// {
//     this->_backgroundRect->setPosition(position);
//     this->_checkRect->setPosition(this->_getCheckPos(position));
// }

// void CheckboxFactory::setSize(const MyVector2 size)
// {
//     this->_backgroundRect->setSize(size);
//     this->_checkRect->setSize(this->_getCheckSize(size));
// }

// void CheckboxFactory::setEnableColor(const RColor color)
// {
//     this->_enableColor = color;
//     if (this->_checked)
//         this->_checkRect->setColor(this->_enableColor);
// }

// void CheckboxFactory::setDisableColor(const raylib::RColor color)
// {
//     this->_disableColor = color;
//     if (!this->_checked)
//         this->_checkRect->setColor(this->_disableColor);
// }

// void CheckboxFactory::toggleCheck()
// {
//     this->_checked = !this->_checked;
//     this->_checkRect->setColor(this->_getCheckColor());
// }

// bool CheckboxFactory::isChecked() const
// {
//     return this->_checked;
// }

// MyVector2 CheckboxFactory::_getCheckPos(const MyVector2 position) const
// {
//     return position + this->_outlineSize;
// }

// MyVector2 CheckboxFactory::_getCheckSize(const MyVector2 size) const
// {
//     return size - 2 * this->_outlineSize;
// }

// RColor CheckboxFactory::_getCheckColor() const
// {
//     return this->_checked ? this->_enableColor : this->_disableColor;
// }

// void CheckboxFactory::_clickHandler(const Engine::Entity)
// {
//     this->toggleCheck();
// }