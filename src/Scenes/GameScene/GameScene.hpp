/*
** EPITECH PROJECT, 2021
** Scenes
** File description:
** 03/06/2021 GameScene.hpp.h
*/

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "GameEngine.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "GUI/Factories/Inventory/InventoryFactory.hpp"

namespace Game
{
    class GameScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        GameScene(Engine::SystemManager &systemManager);
        ~GameScene() = default;

        void open();

        void update();
    };
} // namespace Game

#endif // GAME_SCENE_HPP
