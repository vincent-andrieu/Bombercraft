/*
 * EPITECH PROJECT, 2021
 * Checkbox
 * File description:
 * CheckboxEntity.hpp - Created: 07/06/2021
 */

#ifndef CHECKBOX_ENTITY_HPP
#define CHECKBOX_ENTITY_HPP

#include "Game/CoreData/CoreData.hpp"
#include "Components/ClickEvent.hpp"

#define CHECKBOX_CONFIG_SIZE          "CHECKBOX_SIZE"
#define CHECKBOX_CONFIG_OUTLINE       "CHECKBOX_OUTLINE"
#define CHECKBOX_CONFIG_OUTLINE_COLOR "CHECKBOX_OUTLINE_COLOR"
#define CHECKBOX_CONFIG_ENABLE_COLOR  "CHECKBOX_ENABLE_COLOR"
#define CHECKBOX_CONFIG_DISABLE_COLOR "CHECKBOX_DISABLE_COLOR"

namespace GUI
{
    class CheckboxFactory {
      public:
        CheckboxFactory() = delete;
        ~CheckboxFactory() = delete;

        static void create(Engine::EntityPack &entityPack,
            const raylib::MyVector2 &position,
            Component::eventScript clickHandler,
            bool isDefaultChecked = false);
        static raylib::RColor getCheckColor(bool isChecked);

      private:
        static const Game::EventRequirement _clickHandlerRequirements;
    };
} // namespace GUI

// class CheckboxFactory {
//   public:
//     CheckboxFactory(Engine::SystemManager &systemManager, const MyVector2 position, const MyVector2 size,
//         const MyVector2 outlineSize, const RColor outlineColor = RColor::RWHITE, const RColor enableColor = RColor::RGREEN,
//         const RColor disableColor = RColor::RRED);
//     ~CheckboxFactory() = default;

//     void setPosition(const MyVector2 position);
//     void setSize(const MyVector2 size);
//     void setEnableColor(const RColor color);
//     void setDisableColor(const RColor color);
//     void toggleCheck();
//     [[nodiscard]] bool isChecked() const;

//   private:
//     MyVector2 _getCheckPos(const MyVector2 position) const;
//     MyVector2 _getCheckSize(const MyVector2 size) const;
//     RColor _getCheckColor() const;
//     void _clickHandler(const Engine::Entity);

//     static const Game::EventRequirement _clickHandlerRequirements(Game::evtMouse::LEFT | Game::evtMouse::RIGHT);

//     MyVector2 _outlineSize;
//     RColor _enableColor;
//     RColor _disableColor;
//     std::shared_ptr<raylib::Rectangle> _backgroundRect;
//     std::shared_ptr<raylib::Rectangle> _checkRect;
//     bool _checked = false;
// };

#endif