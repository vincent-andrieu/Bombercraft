/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 ButtonEntity.cpp.cc
*/

#include "ButtonFactory.hpp"

using namespace Game;

ButtonStaticConfig::ButtonStaticConfig(const std::string &texturePath, const raylib::MyVector2 &size, std::size_t fontSize,
    raylib::RColor fontColor, const std::string &fontPath, const EventRequirement &requirements)
    : texturePath(texturePath), size(size), fontSize(fontSize), fontColor(fontColor), fontPath(fontPath),
      requirements(requirements)
{
}

ButtonDynamicConfig::ButtonDynamicConfig(
    const raylib::MyVector2 &position, const std::string &label, Component::eventScript &handler)
    : position(position), label(label), handler(handler)
{
}