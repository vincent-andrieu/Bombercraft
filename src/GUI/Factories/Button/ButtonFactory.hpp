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
        const string unavailableTexturePath;
        raylib::MyVector2 size;
        std::size_t fontSize;
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
        static ButtonConfig getSizedButtonConfig(const raylib::MyVector2 &winPercent);
        static ButtonConfig getLargeButtonConfig();
        static ButtonConfig getMediumButtonConfig();
        static ButtonConfig getBigButtonConfig();
        static ButtonConfig getBighHighButtonConfig();
        static ButtonConfig getSmallButtonConfig();

        static Engine::Entity create(Engine::EntityPack &pack,
            const raylib::MyVector2 &position,
            const string &name,
            ButtonConfig const &conf,
            const string &label,
            const Component::eventScript clickAction,
            bool centered = false);

        static Engine::Entity create(
            Engine::EntityPack &pack,
            const raylib::MyVector2 &position,
            ButtonConfig const &conf,
            const Component::eventScript clickAction,
            const Component::eventScript righClickAction =
                [](Engine::Entity) {
                },
            const string &screenPath = "",
            const string &label = "",
            bool centered = false,
            const string &name = "");

        static const raylib::MyVector2 SmallProportions;
        static const raylib::MyVector2 MediumProportions;
        static const raylib::MyVector2 BigProportions;
        static const raylib::MyVector2 LargeProportions;
        static const raylib::MyVector2 BigHighProportions;
    };

} // namespace GUI

#endif // BUTTONFACTORY_HPP