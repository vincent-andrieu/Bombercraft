/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** CreditScene
*/

#ifndef CREDITSCENE_HPP_
#define CREDITSCENE_HPP_

#include "GameEngine.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Scenes/MainMenu/MainMenuScene.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Utilities/ProportionUtilities.hpp"

#include "GUI/Factories/Label/LabelFactory.hpp"
#include "GUI/Factories/Image/ImageFactory.hpp"
#include "Game/Factories/KeyManagementFactory/KeyManagementFactory.hpp"

#include "Systems/Render2D/Render2DSystem.hpp"

namespace Game
{
    class CreditScene : public Engine::AbstractScene, public SceneWithEvents {
        public:
            CreditScene(Engine::SystemManager &systemManager);
            ~CreditScene() = default;

            virtual void open();

            void update();

        protected:
        private:
    };
}

#endif /* !CREDITSCENE_HPP_ */
