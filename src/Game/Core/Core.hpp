/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Core.hpp.h
*/

#ifndef CORE_HPP
#define CORE_HPP

#include "Game/CoreData/CoreData.hpp"

#include "raylib.hpp"
#include "GameEngine.hpp"

#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Systems/Hitbox/HitboxSystem.hpp"
#include "Systems/Event/EventSystem.hpp"
#include "Systems/Physics/PhysicsSystem.hpp"
#include "Systems/PlayerConfig/PlayerConfigSystem.hpp"

#include "Scenes/KeyBindingMenu/KeyBindingMenuScene.hpp"
#include "Scenes/DebugScene/DebugScene.hpp"
#include "Scenes/SplashScreen/SplashScreenScene.hpp"
#include "Scenes/PauseMenuScene/PauseMenuScene.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Scenes/OptionsMenu/OptionsMenuScene.hpp"
#include "Scenes/LoadingScreen/LoadingScreenScene.hpp"

#include "Game/SceneLoader/SceneLoader.hpp"

#include "Components/KeyBox.hpp"
#include "Components/ClickEvent/ClickEvent.hpp"
#include "Components/KeyEvent.hpp"
#include "Components/FocusEvent/ClickFocusEvent.hpp"
#include "Components/TextInputConfig/TextInputConfig.hpp"
#include "Components/MouseMoveEvent/MouseMoveEvent.hpp"
#include "Components/Hitbox/Hitbox.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"
#include "Components/PlayerInventory/PlayerInventory.hpp"

namespace Game
{
    class Core : public CoreData {
      public:
        Core();
        ~Core() = default;

        void loop();

      public:
        Engine::EntityPack globalEntities;
    };
} // namespace Game

#endif // CORE_HPP