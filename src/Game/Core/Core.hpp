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
#include "Scenes/CreditScene/CreditScene.hpp"
#include "Scenes/LoadingScreen/LoadingScreenScene.hpp"
#include "Scenes/EndGame/EndGameScene.hpp"

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
#include "Preloader/Preloader.hpp"

namespace Game
{
    class Core : public CoreData {
      public:
        Core();
        ~Core() = default;

        void loop();

      private:
        void registerComponents();
        void createSystems();
        void createScenes();
        void loadMusic();
        std::unordered_map<std::string, std::string> getAudioList(std::string const &varPathList, std::string const &varNameList) const;
        bool isEndPreload();
        void printDuringPreload();
        void runPreload();
        void runAfterPreload();

      public:
        Engine::EntityPack globalEntities;
        bool _preloadStatus;
        Preloader<Texture2D, std::string> _preloadTexture;
        Preloader<RModel, std::tuple<std::string, std::string>> _preloadModel;
    };
} // namespace Game

#endif // CORE_HPP