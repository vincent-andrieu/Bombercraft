/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 CountdownFactory.hpp.h
*/

#ifndef COUNTDOWNFACTORY_HPP
#define COUNTDOWNFACTORY_HPP

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "raylib.hpp"

namespace GUI
{
    using CountDownTimeout = std::function<void()>;

    struct TimerConfig {
        const std::string pathTexture;
        const std::string pathFont;
        std::size_t fontSize;
        raylib::RColor textColor;
        raylib::MyVector2 size;
    };

#define DEFAULT_REFRESH_TIME 1.0f

    class CountdownFactory {
      public:
        virtual ~CountdownFactory() = 0;

        static const TimerConfig getStandardConfig();

        static void create(Engine::EntityPack &entityPack,
            raylib::MyVector2 position,
            TimerConfig const &config,
            std::size_t countdown,
            CountDownTimeout handler,
            std::string const &name = "",
            std::size_t refreshMsTime = DEFAULT_REFRESH_TIME);

        static void create(Engine::EntityPack &entityPack,
            raylib::MyVector2 position,
            std::size_t countdown,
            CountDownTimeout handler,
            std::string const &name = "",
            std::size_t refreshMsTime = DEFAULT_REFRESH_TIME);
    };
} // namespace GUI

#endif // COUNTDOWNFACTORY_HPP
