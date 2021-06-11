/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 SplashScreenScene.hpp.h
*/

#ifndef SPLASH_SCREEN_HPP
#define SPLASH_SCREEN_HPP

#include "GameEngine.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"
#include "Game/CoreData/CoreData.hpp"

namespace Game
{
    class SplashScreenScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        SplashScreenScene(Engine::SystemManager &systemManager);
        ~SplashScreenScene() = default;

        void open();

        void update();
    };
} // namespace Game

#endif // SPLASH_SCREEN_HPP
