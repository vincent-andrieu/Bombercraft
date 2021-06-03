/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.hpp.h
*/

#ifndef DEBUGSCENE_HPP
#define DEBUGSCENE_HPP

#include "GameEngine.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"

namespace Game
{
    class DebugScene : public Engine::AbstractScene {
      public:
        DebugScene(Engine::SystemManager &systemManager, Engine::EntityManager &entityManager);
        ~DebugScene() = default;

        void update();
    };
}

#endif // DEBUGSCENE_HPP
