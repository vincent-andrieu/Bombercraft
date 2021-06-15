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
        const raylib::RColor fontColor;
        const std::string fontPath;
    };

    class LabelFactory {
      public:
        ~LabelFactory() = delete;

        static LabelConfig getStandardLabelConfig(std::size_t fontSize = Game::CoreData::settings->getInt("STANDARD_FONT_SIZE"));

        // TODO: add name on entity (modifiate the size of the box)
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

        static void createCentered(Engine::EntityPack &pack,
            raylib::MyVector2 position,
            std::string const &label,
            LabelConfig const &config,
            const std::string &name = "");

      protected:
      private:
    };
} // namespace GUI

#endif /* !LABELFACTORY_HPP_*/