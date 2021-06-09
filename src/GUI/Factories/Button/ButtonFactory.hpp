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
#include "Components/Render2D/SingleRender2D.hpp"

namespace GUI
{
    struct ButtonConfig {
        const std::string idleTexturePath;
        const std::string hoverTexturePath;
        const std::string clickedTexturePath;
        const std::string unavailableTexturePath;
        const raylib::MyVector2 size;
        const std::size_t fontSize;
        const raylib::RColor fontColor;
        const std::string fontPath;
        const Game::EventRequirement requirements;
    };

    class ButtonFactory {
      public:
        virtual ~ButtonFactory() = 0;

        /**
         * @brief Build the standard config for a button
         * @throw If configuration file information retrieval fails
         */
        static ButtonConfig getStandardButtonConfig();

        static Component::eventScript getStandardButtonHandler();

        static void create(Engine::EntityPack &pack,
            const raylib::MyVector2 &position,
            const string &label,
            Component::eventScript &handler,
            ButtonConfig const &conf,
            const std::string &text);
    };
} // namespace GUI

#endif // BUTTONFACTORY_HPP