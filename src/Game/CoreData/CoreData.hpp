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

#ifndef CONFIG_FILE
    #define CONFIG_FILE "bombercraft.config"
#endif
#define UNUSED [[maybe_unused]]

namespace Game
{
    class CoreData {
      public:
        CoreData();
        ~CoreData();

        static void moveCamera(const raylib::MyVector3 &position, const raylib::MyVector3 &target);
        static void quit();

      public:
        static std::unique_ptr<ConfigFile> settings;
        static std::unique_ptr<raylib::Camera> camera;
        static std::shared_ptr<Engine::EntityManager> entityManager;
        static std::shared_ptr<Engine::SceneManager> sceneManager;
        static std::shared_ptr<raylib::Input> eventManager;
        static std::unique_ptr<Engine::SystemManager> systemManager;
        static std::unique_ptr<raylib::Window> window;

      protected:
        static bool _loop;
    };
} // namespace Game

#define CONF_GET_COLOR(label) static_cast<raylib::RColor>(CoreData::settings->getInt(label))

#endif // COREDATA_HPP