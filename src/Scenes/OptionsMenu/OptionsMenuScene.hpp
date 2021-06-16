/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** OptionsMenu
*/

#ifndef OPTIONSMENU_HPP_
#define OPTIONSMENU_HPP_

#include "GameEngine.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "GUI/Factories/Image/ImageFactory.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "GUI/Factories/Slider/SliderFactory.hpp"

#include "Systems/Render2D/Render2DSystem.hpp"

#include "Components/Option/OptionComponent.hpp"

namespace Game
{
    class OptionsMenuScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        OptionsMenuScene(Engine::SystemManager &systemManager);
        ~OptionsMenuScene() = default;

        virtual void open();

        void update();

      protected:
      private:
    };
} // namespace Game

#endif /* !OPTIONSMENU_HPP_ */