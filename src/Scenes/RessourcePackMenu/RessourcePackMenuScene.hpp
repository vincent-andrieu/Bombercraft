/*
 * EPITECH PROJECT, 2021
 * RessourcePackMenu
 * File description:
 * RessourcePackMenuScene.hpp - Created: 15/06/2021
 */

#ifndef RESSOURCE_PACK_MENU_SCENE_HPP
#define RESSOURCE_PACK_MENU_SCENE_HPP

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Utilities/ProportionUtilities.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"

namespace Game
{
    class RessourcePackMenuScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        RessourcePackMenuScene(Engine::SystemManager &systemManager);
        ~RessourcePackMenuScene() = default;

        void open() override;

        void update() override;
    };
} // namespace Game

#endif // DEBUGSCENE_HPP