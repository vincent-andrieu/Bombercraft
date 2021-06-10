/*
 * EPITECH PROJECT, 2021
 * Slider
 * File description:
 * SliderEntity.hpp - Created: 10/06/2021
 */

#ifndef SLIDER_ENTITY_HPP
#define SLIDER_ENTITY_HPP

#include "Game/CoreData/CoreData.hpp"
#include "Components/ClickEvent.hpp"

#define SLIDER_CONFIG_SIZE             "SLIDER_SIZE"
#define SLIDER_CONFIG_BACKGROUND_COLOR "SLIDER_BACKGROUND_COLOR"
#define SLIDER_CONFIG_SELECTOR_SIZE    "SLIDER_SELECTOR_SIZE"
#define SLIDER_CONFIG_SELECTOR_COLOR   "SLIDER_SELECTOR_COLOR"

namespace GUI
{
    typedef int sliderValue;
    using sliderHandler = std::function<void(const Engine::Entity, sliderValue &)>;

    class SliderFactory {
      public:
        SliderFactory() = delete;
        ~SliderFactory() = delete;

        static void create(Engine::EntityPack &entityPack, const raylib::MyVector2 &position, sliderHandler clickHandler,
            sliderValue minValue = 0, sliderValue maxValue = 100, sliderValue defaultValue = 0);

      private:
        static const Game::EventRequirement _clickHandlerRequirements;
        static float _getRangeValue(const float &origin, const sliderValue &minValue, const sliderValue &maxValue,
            const sliderValue &value, const float &size = Game::CoreData::settings->getMyVector2(SLIDER_CONFIG_SIZE).a,
            const float &selectorSize = Game::CoreData::settings->getMyVector2(SLIDER_CONFIG_SELECTOR_SIZE).a);

        static sliderValue _getValueFromRange(const float &position, const sliderValue &maxValue,
            const raylib::MyVector2 &size = Game::CoreData::settings->getMyVector2(SLIDER_CONFIG_SIZE));

        static const raylib::MyVector2 _getSliderMousePos(const raylib::MyVector2 &position,
            const float &mousePos = Game::CoreData::eventManager->getMousePos().a,
            const float &size = Game::CoreData::settings->getMyVector2(SLIDER_CONFIG_SIZE).a,
            const raylib::MyVector2 &selectorSize = Game::CoreData::settings->getMyVector2(SLIDER_CONFIG_SELECTOR_SIZE));
    };
} // namespace GUI

#endif