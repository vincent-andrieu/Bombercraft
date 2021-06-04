/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.hpp.h
*/

#ifndef CORE_HPP
#define CORE_HPP

#include "raylib.hpp"
#include "GameEngine.hpp"

#include "Components/Hitbox/Hitbox.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Scenes/DebugScene/DebugScene.hpp"
#include "ConfigFile/ConfigFile.hpp"

namespace Game
{
    class Core {
      public:
        Core();
        ~Core() = default;

        void loop();

      public:
        static std::unique_ptr<raylib::Camera> camera;
        static Engine::SceneManager sceneManager;
        static Engine::EntityManager entityManager;

      private:
        ConfigFile _settings;
        raylib::Window _window;
        static Engine::SystemManager _systemManager;
    };
} // namespace Game

#endif // CORE_HPP
