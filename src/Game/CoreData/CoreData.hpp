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

      protected:
        static std::shared_ptr<Engine::SystemManager> _systemManager;
        static std::unique_ptr<raylib::Window> _window;
    };
} // namespace Game

#endif // COREDATA_HPP
