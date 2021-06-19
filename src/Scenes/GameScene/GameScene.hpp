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
#include "Components/Option/OptionComponent.hpp"

namespace Game
{
    extern const std::unordered_map<Component::PlayerID, std::string> PLAYER_ID_TO_NAME;

    class GameScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        GameScene(Engine::SystemManager &systemManager);
        ~GameScene() = default;

        void loadGame(const std::string &loadName);
        void saveGame(const std::string &saveName);
        void cameraAnimation(const raylib::MyVector3 &toCameraPosition,
            const raylib::MyVector3 &toCameraUp,
            const raylib::MyVector3 &toCameraTarget);
        void open();
        static uint getNbrPlayers();

        void update();

      private:
        void createCharacters();

        void loadPlayerConfig();
        void savePlayerConfig();
    };
} // namespace Game

#endif // GAME_SCENE_HPP