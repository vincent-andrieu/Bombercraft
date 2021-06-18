/*
** EPITECH PROJECT, 2021
** PauseMenuScene.hpp
** File description:
** Pause menu, during a game
*/

#ifndef BOMBERMAN_PAUSEMENUSCENE_HPP
#define BOMBERMAN_PAUSEMENUSCENE_HPP

#include "AbstractScene/AbstractScene.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Components/ModelList/ModelList.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"

namespace Game
{
    class PauseMenuScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        explicit PauseMenuScene(Engine::SystemManager &systemManager);
        ~PauseMenuScene() = default;

        void open() override;
        void update() override;
        //        void close();
    };
} // namespace Game

#endif // BOMBERMAN_PAUSEMENUSCENE_HPP