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

#include "Components/ClickEvent/ClickEvent.hpp"
#include "Components/MouseMoveEvent/MouseMoveEvent.hpp"
#include "Components/Render2D/Render2D.hpp"

namespace GUI
{
    struct ButtonConfig {
        const string idleTexturePath;
        const string hoverTexturePath;
        const string clickedTexturePath;
        const string unavailableTexturePath;
        const raylib::MyVector2 size;
        const std::size_t fontSize;
        const raylib::RColor fontColor;
        const string fontPath;
        const Game::EventRequirement &requirements;
    };

    class ButtonFactory {
      public:
        virtual ~ButtonFactory() = 0;

        /**
         * @brief Build the standard config for a button
         * @throw If configuration file information retrieval fails
         */
        static ButtonConfig getStandardButtonConfig(const raylib::MyVector2 &buttonSize = raylib::MyVector2(180, 20));

        static void create(Engine::EntityPack &pack,
            const raylib::MyVector2 &position,
            const string &name,
            ButtonConfig const &conf,
            const string &label,
            const Component::eventScript clickAction);
    };
} // namespace GUI

#endif // BUTTONFACTORY_HPP