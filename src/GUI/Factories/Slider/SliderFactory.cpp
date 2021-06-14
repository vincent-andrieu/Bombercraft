/*
 * EPITECH PROJECT, 2021
 * Checkbox
 * File description:
 * CheckboxEntity.cpp - Created: 07/06/2021
 */

#include "SliderFactory.hpp"
#include "Components/Render2D/Render2D.hpp"
#include "Utilities/ProportionUtilities.hpp"

using namespace raylib;
using namespace GUI;
using namespace Game;

const EventRequirement SliderFactory::_clickHandlerRequirements(Game::CLK_LEFT | Game::CLK_RIGHT);

void SliderFactory::create(Engine::EntityPack &entityPack,
    const MyVector2 &position,
    sliderHandler sliderHandler,
    const string &label,
    const MyVector2 &size,
    sliderValue minValue,
    sliderValue maxValue,
    sliderValue defaultValue,
    const bool centered)
{
    const auto entity = entityPack.createAnonymousEntity();
    const MyVector2 &selectorSize =
        MyVector2(static_cast<float>(CoreData::settings->getInt(SLIDER_CONFIG_SELECTOR_SIZE)), size.b);

    auto my_position(position);
    if (centered)
        my_position = my_position - ProportionUtilities::getProportionWin(size, raylib::MyVector2(50, 50));

    const auto &background =
        std::make_shared<raylib::Rectangle>(my_position, size, CONF_GET_COLOR(SLIDER_CONFIG_BACKGROUND_COLOR));
    auto selector = std::make_shared<raylib::Rectangle>(
        MyVector2(SliderFactory::_getRangeValue(my_position.a, minValue, maxValue, defaultValue, size.a, selectorSize.a),
            my_position.b),
        selectorSize,
        CONF_GET_COLOR(SLIDER_CONFIG_SELECTOR_COLOR));
    auto displayLabel = std::make_shared<raylib::Text>(label + toString(defaultValue),
        my_position,
        CoreData::settings->getInt(SLIDER_CONFIG_LABEL_SIZE),
        CONF_GET_COLOR(SLIDER_CONFIG_LABEL_COLOR));
    displayLabel->setPosition(
        my_position + ProportionUtilities::getProportionWin(size, MyVector2(50, 50), displayLabel->getSize(), MyVector2(50, 50)));

    Component::eventScript clickHandler =
        [selector, displayLabel, label, my_position, size, selectorSize, minValue, maxValue, defaultValue, sliderHandler](
            const Engine::Entity entity) {
            if (CoreData::eventManager->MouseIsOverClicked(my_position, size)) {
                static sliderValue value = defaultValue;
                const MyVector2 &mousePos = CoreData::eventManager->getMousePos();
                const MyVector2 &sliderPos = SliderFactory::_getSliderMousePos(my_position, mousePos.a, size.a, selectorSize);

                value = SliderFactory::_getValueFromRange(mousePos.a - my_position.a, maxValue, size);
                selector->setPosition(sliderPos);
                displayLabel->setText(label + toString(value));
                sliderHandler(entity, value);
            }
        };

    CoreData::entityManager->addComponent<Component::Render2D>(entity,
        Component::render2dMapModels{
            {"sliderSelector", selector}, {"sliderLabel", displayLabel}, {"sliderBackground", background}});
    CoreData::entityManager->addComponent<Component::ClickEvent>(entity, clickHandler, SliderFactory::_clickHandlerRequirements);
}

float SliderFactory::_getRangeValue(const float &origin,
    const sliderValue &minValue,
    const sliderValue &maxValue,
    const sliderValue &value,
    const float &size,
    const float &selectorSize)
{
    if (value < minValue || value > maxValue)
        throw std::out_of_range("slider value is over limits");
    float pos = origin + ((size * value) / maxValue) + minValue - (selectorSize / 2);

    if (pos < origin)
        pos = origin;
    if (pos + selectorSize > origin + size)
        pos = origin + size - selectorSize;
    return pos;
}

sliderValue SliderFactory::_getValueFromRange(const float &position, const sliderValue &maxValue, const MyVector2 &size)
{
    if (position < 0 || position > size.a)
        throw std::out_of_range("slider position is over limits");
    return (int) ((position * maxValue) / size.a);
}

const MyVector2 SliderFactory::_getSliderMousePos(
    const MyVector2 &position, const float &mousePos, const float &size, const MyVector2 &selectorSize)
{
    MyVector2 sliderPos(mousePos - (selectorSize.a / 2), position.b);

    if (sliderPos.a < position.a)
        sliderPos.a = position.a;
    if (sliderPos.a + selectorSize.a > position.a + size)
        sliderPos.a = position.a + size - selectorSize.a;
    return sliderPos;
}