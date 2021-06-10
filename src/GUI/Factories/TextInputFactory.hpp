/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** TextInputFactory
*/

#ifndef TEXTINPUTFACTORY_HPP_
#define TEXTINPUTFACTORY_HPP_

#include <map>

#include "raylib.hpp"

#include "Game/CoreData/CoreData.hpp"

#include "Components/Render2D/Render2D.hpp"
#include "Components/FocusEvent/ClickFocusEvent.hpp"
#include "Components/TextInputConfig/TextInputConfig.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"
#include "Game/EventRequirement/EventRequirement.hpp"
#include "GUI/Factories/LabelFactory.hpp"
#include "GameEngine.hpp"

namespace GUI
{
    struct TextInputConfig {
        const raylib::MyVector2 size;
        const raylib::RColor color;
        const std::size_t borderSize;
        const raylib::RColor borderColor;
        const size_t maxChar;
        const raylib::MyVector2 textPositionOffset;
    };

    struct TextInputDynConf {
        const raylib::MyVector2 position;
        const std::string name;
        const std::string placeholder;
    };

    class TextInputFactory {
        public:
            ~TextInputFactory() = delete;

            static void create(Engine::EntityPack &pack, TextInputDynConf const &dynConf, TextInputConfig const &textInput, LabelConfig const &label);
            static void create(Engine::EntityPack &pack, TextInputDynConf const &dynConf, LabelConfig const &label);
            static TextInputConfig getStandardConfig();
        protected:
        private:
    };
} // namespace GUI

#endif /* !TEXTINPUTFACTORY_HPP_ */
