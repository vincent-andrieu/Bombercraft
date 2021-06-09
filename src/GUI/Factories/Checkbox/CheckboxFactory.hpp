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

        static void create(Engine::EntityPack &entityPack, const raylib::MyVector2 position, Component::eventScript clickHandler,
            bool isDefaultChecked = false);
        static raylib::RColor getCheckColor(bool isChecked);

      private:
        static const Game::EventRequirement _clickHandlerRequirements;
    };
} // namespace GUI

#endif