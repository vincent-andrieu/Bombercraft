/*
** EPITECH PROJECT, 2021
** Scenes
** File description:
** 03/06/2021 EndGameScene.hpp.h
*/

#ifndef ENDGAME_SCENE_HPP
#define ENDGAME_SCENE_HPP

#include "GameEngine.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Scenes/GameScene/GameScene.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "GUI/Factories/XPBar/XPBarFactory.hpp"

namespace Game
{
    class EndGameScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        EndGameScene(Engine::SystemManager &systemManager);
        ~EndGameScene() = default;

        void open();

        void update();

      private:
        static size_t getNbPlayer();
    };
} // namespace Game

#endif // ENDGAME_SCENE_HPP
