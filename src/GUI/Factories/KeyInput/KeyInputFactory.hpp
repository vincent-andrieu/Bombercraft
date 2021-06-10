/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** KeyInputFactory
*/

#ifndef KEYINPUTFACTORY_HPP_
#define KEYINPUTFACTORY_HPP_

#include <map>

#include "raylib.hpp"

#include "GameEngine.hpp"
#include "Game/CoreData/CoreData.hpp"

#include "Components/Render2D/Render2D.hpp"
#include "Components/FocusEvent/ClickFocusEvent.hpp"
#include "Components/TextInputConfig/TextInputConfig.hpp"
#include "Components/KeyBox.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"
#include "GameEngine.hpp"

namespace GUI
{
    struct KeyInputConfig {
        const raylib::MyVector2 size;
        const raylib::RColor color;
        const std::size_t borderSize;
        const raylib::RColor borderColor;
        const raylib::MyVector2 textPositionOffset;
    };

    struct KeyInputDynConf {
        const raylib::MyVector2 position;
        const std::string name;
    };

    class KeyInputFactory {
        public:
            ~KeyInputFactory() = delete;

        static void create(Engine::EntityPack &pack, KeyInputDynConf const &dynConf, KeyInputConfig const &keyInput,
                LabelConfig const &label);
        static void create(Engine::EntityPack &pack, KeyInputDynConf const &dynConf, LabelConfig const &label);
        static KeyInputConfig getStandardConfig();

        protected:
        private:
};
}



#endif /* !KEYINPUTFACTORY_HPP_ */
