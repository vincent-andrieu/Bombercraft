/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 TimerFactory.hpp.h
*/

#ifndef TIMERFACTORY_HPP
#define TIMERFACTORY_HPP

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "raylib.hpp"

namespace GUI
{
    struct TimerConfig {
        const std::string pathTexture;
        const std::string pathFont;
        std::size_t fontSize;
        raylib::RColor textColor;
        raylib::MyVector2 size;
    };

    class TimerFactory {
      public:
        virtual ~TimerFactory() = 0;

        static const TimerConfig getStandardConfig();

        static void create(Engine::EntityPack &entityPack, raylib::MyVector2 position, TimerConfig const &config,
            std::string const &name = "", std::size_t refreshMsTime = 1000);

        static void create(Engine::EntityPack &entityPack, raylib::MyVector2 position, std::string const &name = "",
            std::size_t refreshMsTime = 1000);
    };
} // namespace GUI

#endif // TIMERFACTORY_HPP
