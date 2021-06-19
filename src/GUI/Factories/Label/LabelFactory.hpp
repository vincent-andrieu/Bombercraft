/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** LabelFactory
*/

#ifndef LABELFACTORY_HPP_
#define LABELFACTORY_HPP_

#include "raylib.hpp"

#include "Game/CoreData/CoreData.hpp"

#include "Components/Render2D/Render2D.hpp"
#include "GameEngine.hpp"

namespace GUI
{
    struct LabelConfig {
        const std::size_t fontSize;
        raylib::RColor fontColor;
        const std::string fontPath;
    };

    class LabelFactory {
      public:
        ~LabelFactory() = delete;

        static LabelConfig getStandardLabelConfig(std::size_t fontSize = Game::CoreData::settings->getInt("STANDARD_FONT_SIZE"));

        static void create(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            std::string const &label,
            LabelConfig const &config,
            const std::string &name = "");
        static void create(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            std::size_t const &label,
            LabelConfig const &config,
            const std::string &name = "");
        static void create(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            int const &label,
            LabelConfig const &config,
            const std::string &name = "");
        static void create(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            float const &label,
            LabelConfig const &config,
            const std::string &name = "");

        static void create(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            raylib::MyVector2 size,
            std::string const &label,
            LabelConfig const &config,
            const std::string &name = "",
            const bool centered = false);

        static Engine::Entity createCentered(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            std::string const &label,
            LabelConfig const &config,
            const std::string &name = "");

        static Engine::Entity createCentered(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            raylib::MyVector2 size,
            std::string const &label,
            LabelConfig const &config,
            const std::string &name = "");
    };
} // namespace GUI

#endif /* !LABELFACTORY_HPP_*/