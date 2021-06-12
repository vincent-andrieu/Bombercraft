/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** LoadingScreen
*/

#ifndef LOADING_SCREEN_HPP
#define LOADING_SCREEN_HPP

#include "GameEngine.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "GUI/Factories/Image/ImageFactory.hpp"

#include "Systems/Render2D/Render2DSystem.hpp"

namespace Game
{
    class LoadingScreenScene : public Engine::AbstractScene, public SceneWithEvents {
        public:
            LoadingScreenScene(Engine::SystemManager &systemManager);
            ~LoadingScreenScene() = default;

            virtual void open();

            void update();

        protected:
        private:
    };
}

#endif /* !LOADING_SCREEN_HPP */