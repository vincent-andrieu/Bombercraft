/*
** EPITECH PROJECT, 2021
** B-YEP-400-REN-4-1-indiestudio-simon.racaud
** File description:
** ClickFocusEvent
*/

#include "ClickFocusEvent.hpp"
#include "Components/Render2D/Render2D.hpp"

using namespace Component;

ClickFocusEvent::ClickFocusEvent(eventScript &handler, Game::EventRequirement const &requirements)
    : AbstractEvent(handler, requirements), _isFocus(false)
{
}

bool ClickFocusEvent::getFocus() const
{
    return this->_isFocus;
}

void ClickFocusEvent::changeFocus(bool focus)
{
    this->_isFocus = focus;
}
