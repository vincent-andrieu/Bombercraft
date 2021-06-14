/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 04/06/2021 MainMenuScene.hpp.h
*/

#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "GameEngine.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Scenes/DebugScene/DebugScene.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "GUI/Factories/Image/ImageFactory.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "Utilities/ProportionUtilities.hpp"

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
} // namespace Game

#endif // MAINMENUSCENE_HPP