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

#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Scenes/DebugScene/DebugScene.hpp"

namespace Game
{
    class Core {
      public:
        Core();
        ~Core();

        void loop();

      public:
        static std::unique_ptr<raylib::Camera> camera;
      private:
        raylib::Window _window;
        Engine::SystemManager _systemManager;
        Engine::EntityManager _entityManager;
        Engine::SceneManager _sceneManager;
    };
}

#endif // CORE_HPP
