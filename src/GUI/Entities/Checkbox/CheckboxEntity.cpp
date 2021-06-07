/*
 * EPITECH PROJECT, 2021
 * Checkbox
 * File description:
 * CheckboxEntity.cpp - Created: 07/06/2021
 */

#include "CheckboxEntity.hpp"
#include "Components/Render2D/Render2D.hpp"
#include "Components/ClickEvent.hpp"

using namespace raylib;

CheckboxEntity::CheckboxEntity(Engine::SystemManager &systemManager, const MyVector2 position, const MyVector2 size,
    const MyVector2 outlineSize, const RColor outlineColor, const RColor enableColor, const RColor disableColor)
    : _outlineSize(outlineSize), _enableColor(enableColor), _disableColor(disableColor),
      _backgroundRect(std::make_shared<raylib::Rectangle>(position, size, outlineColor)),
      _checkRect(std::make_shared<raylib::Rectangle>(position + outlineSize, size - 2 * outlineSize, disableColor))
{
    // auto checkbox = this->_entityPack.createEntity("checkbox");
    auto checkbox = Game::CoreData::entityManager->createEntity();

    Game::CoreData::entityManager->addComponent<Component::Render2D>(
        checkbox, Component::render2dMapModels{{"background", this->_backgroundRect}, {"check", this->_checkRect}});
    Game::CoreData::entityManager->addComponent<Component::ClickEvent>(
        checkbox, CheckboxEntity::_clickHandler, this->_clickHandlerRequirements);
}

void CheckboxEntity::setPosition(const MyVector2 position)
{
    this->_backgroundRect->setPosition(position);
    this->_checkRect->setPosition(this->_getCheckPos(position));
}

void CheckboxEntity::setSize(const MyVector2 size)
{
    this->_backgroundRect->setSize(size);
    this->_checkRect->setSize(this->_getCheckSize(size));
}

void CheckboxEntity::setEnableColor(const RColor color)
{
    this->_enableColor = color;
    if (this->_checked)
        this->_checkRect->setColor(this->_enableColor);
}

void CheckboxEntity::setDisableColor(const raylib::RColor color)
{
    this->_disableColor = color;
    if (!this->_checked)
        this->_checkRect->setColor(this->_disableColor);
}

void CheckboxEntity::toggleCheck()
{
    this->_checked = !this->_checked;
    this->_checkRect->setColor(this->_getCheckColor());
}

bool CheckboxEntity::isChecked() const
{
    return this->_checked;
}

MyVector2 CheckboxEntity::_getCheckPos(const MyVector2 position) const
{
    return position + this->_outlineSize;
}

MyVector2 CheckboxEntity::_getCheckSize(const MyVector2 size) const
{
    return size - 2 * this->_outlineSize;
}

RColor CheckboxEntity::_getCheckColor() const
{
    return this->_checked ? this->_enableColor : this->_disableColor;
}

void CheckboxEntity::_clickHandler(const Engine::Entity)
{
    this->toggleCheck();
}