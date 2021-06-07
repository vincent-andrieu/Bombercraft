/*
 * EPITECH PROJECT, 2021
 * Checkbox
 * File description:
 * CheckboxEntity.hpp - Created: 07/06/2021
 */

#ifndef CHECKBOX_ENTITY_HPP
#define CHECKBOX_ENTITY_HPP

#include "raylib.hpp"
#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"

class CheckboxEntity {
  public:
    CheckboxEntity(Engine::SystemManager &systemManager, const MyVector2 position, const MyVector2 size,
        const MyVector2 outlineSize, const RColor outlineColor = RColor::RWHITE, const RColor enableColor = RColor::RGREEN,
        const RColor disableColor = RColor::RRED);
    ~CheckboxEntity() = default;

    void setPosition(const MyVector2 position);
    void setSize(const MyVector2 size);
    void setEnableColor(const RColor color);
    void setDisableColor(const RColor color);
    void toggleCheck();
    [[nodiscard]] bool isChecked() const;

  private:
    MyVector2 _getCheckPos(const MyVector2 position) const;
    MyVector2 _getCheckSize(const MyVector2 size) const;
    RColor _getCheckColor() const;
    void _clickHandler(const Engine::Entity);

    static const Game::EventRequirement _clickHandlerRequirements(Game::evtMouse::LEFT | Game::evtMouse::RIGHT);

    MyVector2 _outlineSize;
    RColor _enableColor;
    RColor _disableColor;
    std::shared_ptr<raylib::Rectangle> _backgroundRect;
    std::shared_ptr<raylib::Rectangle> _checkRect;
    bool _checked = false;
};

#endif