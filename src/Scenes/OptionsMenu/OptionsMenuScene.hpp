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
#include "Game/CoreData/CoreData.hpp"

#include "GUI/Factories/Image/ImageFactory.hpp"

#include "Systems/Render2D/Render2DSystem.hpp"

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
}

#endif /* !OPTIONSMENU_HPP_ */