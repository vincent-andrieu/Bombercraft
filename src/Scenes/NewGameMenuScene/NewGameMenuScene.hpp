/*
** EPITECH PROJECT, 2021
** NewGameMenuScene.hpp
** File description:
** Scene to display previous games before choosing or creating one to play
*/
#ifndef BOMBERMAN_NEWGAMEMENUSCENE_HPP
#define BOMBERMAN_NEWGAMEMENUSCENE_HPP

#include "GameEngine.hpp"
#include <Components/Option/OptionComponent.hpp>
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"

namespace Game
{
    class NewGameMenuScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        NewGameMenuScene(Engine::SystemManager &systemManager);
        ~NewGameMenuScene() = default;

        void setStandardOptions(Component::OptionComponent &options);
        void init();
        void open() override;

        void update() override;
    };
} // namespace Game

#endif // BOMBERMAN_NEWGAMEMENUSCENE_HPP