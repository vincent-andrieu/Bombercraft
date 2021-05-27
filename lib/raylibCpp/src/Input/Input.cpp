/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Input.cpp
*/

#include "Input.hpp"

using namespace raylib;

Input::Input()
{
}

Input::~Input()
{
}

bool Input::isKeyPressed(KeyBoard key) const
{
    std::unordered_map<KeyBoard, int>::const_iterator keyLine = this->_keyList.find(key);

    if (keyLine == this->_keyList.end())
        throw std::invalid_argument("isKeyPressed: key not found.");
    return IsKeyDown(keyLine->second);
}

bool Input::isKeyReleased(KeyBoard key) const
{
    return !this->isKeyPressed(key);
}

MyVector2 Input::getMousePos(void) const
{
    Vector2 pos = GetMousePosition();

    return MyVector2(pos.x, pos.y);
}

bool Input::isMousseLeftPressed(void) const
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool Input::isMousseRightPressed(void) const
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
}

bool Input::isMousseMiddlePressed(void) const
{
    return IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE);
}