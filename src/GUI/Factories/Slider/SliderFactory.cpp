/*
 * EPITECH PROJECT, 2021
 * Checkbox
 * File description:
 * CheckboxEntity.cpp - Created: 07/06/2021
 */

#include "SliderFactory.hpp"
#include "Components/Render2D/Render2D.hpp"

using namespace raylib;
using namespace GUI;
using namespace Game;

const EventRequirement SliderFactory::_clickHandlerRequirements(evtMouse::LEFT | evtMouse::RIGHT);

void SliderFactory::create(Engine::EntityPack &entityPack, const MyVector2 &position, sliderHandler sliderHandler,
    sliderValue minValue, sliderValue maxValue, sliderValue defaultValue)
{
    const auto entity = entityPack.createAnonymousEntity();
    const MyVector2 &size = CoreData::settings->getMyVector2(SLIDER_CONFIG_SIZE);
    const MyVector2 &selectorSize = CoreData::settings->getMyVector2(SLIDER_CONFIG_SELECTOR_SIZE);

    auto background = std::make_shared<raylib::Rectangle>(
        position, size, static_cast<RColor>(CoreData::settings->getInt(SLIDER_CONFIG_BACKGROUND_COLOR)));
    auto selector = std::make_shared<raylib::Rectangle>(
        MyVector2(position.a + SliderFactory::_getRangeValue(minValue, maxValue, defaultValue), position.b), selectorSize,
        static_cast<RColor>(CoreData::settings->getInt(SLIDER_CONFIG_SELECTOR_COLOR)));

    Component::eventScript clickHandler = [selector, position, size, selectorSize, minValue, maxValue, defaultValue,
                                              sliderHandler](const Engine::Entity entity) {
        if (CoreData::eventManager->MouseIsOverClicked(position, size)) {
            static sliderValue value = defaultValue;
            const MyVector2 &mousePos = CoreData::eventManager->getMousePos();

            selector->setPosition(MyVector2(mousePos.a + (selectorSize.a / 2), position.b));
            sliderHandler(entity, value);
        }
    };

    CoreData::entityManager->addComponent<Component::Render2D>(
        entity, Component::render2dMapModels{{"sliderSelector", selector}, {"sliderBackground", background}});
    CoreData::entityManager->addComponent<Component::ClickEvent>(entity, clickHandler, SliderFactory::_clickHandlerRequirements);
}

float SliderFactory::_getRangeValue(sliderValue minValue, sliderValue maxValue, sliderValue value, MyVector2 size)
{
    if (value < minValue || value > maxValue)
        throw std::out_of_range("slider value is over limits");
    return ((size.a * value) / maxValue) + minValue;
}