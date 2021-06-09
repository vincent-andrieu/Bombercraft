/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 MainMenuScene.hpp.h
*/

#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "GameEngine.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "Systems/Render2D/Render2DSystem.hpp"

namespace Game
{
    class MainMenuScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        MainMenuScene(Engine::SystemManager &systemManager);
        ~MainMenuScene() = default;

        virtual void open();

        void update();
    };
}

#endif // MAINMENUSCENE_HPP
