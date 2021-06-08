/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 07/06/2021 ButtonFactory.hpp.h
*/

#ifndef BUTTONFACTORY_HPP
#define BUTTONFACTORY_HPP

#include "raylib.hpp"

#include "IFactoryData.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "Components/ClickEvent.hpp"
#include "Components/MouseMoveEvent.hpp"
#include "Components/Render2D/Render2D.hpp"

namespace Game
{
    class ButtonStaticConfig : public IStaticFactoryData {
      public:
        ButtonStaticConfig(std::string const &texturePath, raylib::MyVector2 const &size, std::size_t fontSize,
            raylib::RColor fontColor, std::string const &fontPath, const EventRequirement &requirements);

        std::string texturePath;
        raylib::MyVector2 size;
        std::size_t fontSize;
        raylib::RColor fontColor;
        std::string fontPath;
        EventRequirement requirements;
    };