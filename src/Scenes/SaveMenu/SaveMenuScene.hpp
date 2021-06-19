/*
 * EPITECH PROJECT, 2021
 * SaveMenu
 * File description:
 * SaveMenuScene.hpp - Created: 19/06/2021
 */

#ifndef BOMBERMAN_SAVE_MENU_SCENE_HPP
#define BOMBERMAN_SAVE_MENU_SCENE_HPP

#include "GameEngine.hpp"
#include <Components/Option/OptionComponent.hpp>
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"

namespace Game
{
    class SaveMenuScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        SaveMenuScene(Engine::SystemManager &systemManager);
        ~SaveMenuScene() = default;

        void preLoadGames();

        void open() override;

        void update() override;

      private:
        void createButtonGamePreload(const std::filesystem::path &dir, const size_t entryNb);
    };
} // namespace Game

#endif // BOMBERMAN_SAVE_MENU_SCENE_HPP