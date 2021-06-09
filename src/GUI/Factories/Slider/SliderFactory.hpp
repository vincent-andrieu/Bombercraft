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

#define SLIDER_CONFIG_SIZE             "SLIDER_SIZE"
#define SLIDER_CONFIG_BACKGROUND_COLOR "SLIDER_BACKGROUND_COLOR"
#define SLIDER_CONFIG_SELECTOR_SIZE    "SLIDER_SELECTOR_SIZE"
#define SLIDER_CONFIG_SELECTOR_COLOR   "SLIDER_SELECTOR_COLOR"

typedef int sliderValue;

namespace GUI
{
    using sliderHandler = std::function<void(const Engine::Entity, sliderValue &)>;

    class SliderFactory {
      public:
        SliderFactory() = delete;
        ~SliderFactory() = delete;

        static void create(Engine::EntityPack &entityPack, const raylib::MyVector2 &position, sliderHandler clickHandler,
            sliderValue minValue = 0, sliderValue maxValue = 100, sliderValue defaultValue = 0);

      private:
        static const Game::EventRequirement _clickHandlerRequirements;
        static float _getRangeValue(sliderValue minValue, sliderValue maxValue, sliderValue value,
            raylib::MyVector2 size = Game::CoreData::settings->getMyVector2(SLIDER_CONFIG_SIZE));
    };
} // namespace GUI

#endif