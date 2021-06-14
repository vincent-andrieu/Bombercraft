/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 14/06/2021 SoundOptionScene.hpp.h
*/

#ifndef SOUNDOPTIONSCENE_HPP
#define SOUNDOPTIONSCENE_HPP

#include "GameEngine.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/CoreData/CoreData.hpp"

namespace Game
{
    class SoundOptionScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        SoundOptionScene();
        virtual ~SoundOptionScene() = default;

        void open();

        void update();
    };
}

#endif // SOUNDOPTIONSCENE_HPP
