/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 11/06/2021 SkinChoiceScene.hpp.h
*/

#ifndef SKINCHOICESCENE_HPP
#define SKINCHOICESCENE_HPP

#include "GameEngine.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"

namespace Game
{
    class SkinChoiceScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        SkinChoiceScene();
        virtual ~SkinChoiceScene() = default;

        void update();

        void open();

      private:
        Component::PlayerConfig *_selectedPlayer;
    };
} // namespace Game

#endif // SKINCHOICESCENE_HPP
