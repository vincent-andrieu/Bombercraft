/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 CoreData.hpp.h
*/

#ifndef COREDATA_HPP
#define COREDATA_HPP

#include "raylib.hpp"
#include "GameEngine.hpp"

#include "ConfigFile/ConfigFile.hpp"

#define CONFIG_FILE "bomberman.config"
#define UNUSED      [[maybe_unused]]

namespace Game
{
    class CoreData {
      public:
        CoreData();
        ~CoreData() = default;

      public:
        static std::unique_ptr<ConfigFile> settings;
        static std::shared_ptr<raylib::Camera> camera;
        static std::shared_ptr<Engine::EntityManager> entityManager;
        static std::shared_ptr<Engine::SceneManager> sceneManager;
        static std::shared_ptr<raylib::Input> eventManager;
        static std::shared_ptr<Engine::SystemManager> systemManager;

      protected:
        static std::unique_ptr<raylib::Window> _window;
    };
} // namespace Game

#define CONF_GET_COLOR(label) static_cast<raylib::RColor>(CoreData::settings->getInt(label))

#endif // COREDATA_HPP
