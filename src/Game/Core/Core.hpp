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
#include "Systems/Event/EventSystem.hpp"

#include "Scenes/DebugScene/DebugScene.hpp"
#include "ConfigFile/ConfigFile.hpp"

#include "Components/ClickEvent.hpp"
#include "Components/KeyEvent.hpp"
#include "Components/MouseMoveEvent.hpp"

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
        ConfigFile _settings;
        raylib::Window _window;
        Engine::SystemManager _systemManager;
        Engine::EntityManager _entityManager;
        Engine::SceneManager _sceneManager;
        raylib::Input _eventManager;
    };
} // namespace Game

#endif // CORE_HPP
