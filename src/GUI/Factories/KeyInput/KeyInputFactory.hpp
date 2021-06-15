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
    using KeyInputEventScript = std::function<void(const Engine::Entity &, const std::pair<const raylib::KeyBoard, string> &)>;

    struct KeyInputConfig {
        const raylib::MyVector2 size;
        const raylib::RColor color;
        const raylib::MyVector2 textPositionOffset;
    };

    struct KeyInputDynConf {
        const raylib::MyVector2 position;
        const string name;
        const raylib::KeyBoard key = raylib::KeyBoard::IKEY_NULL;
    };

    class KeyInputFactory {
      public:
        ~KeyInputFactory() = delete;

        static void create(
            Engine::EntityPack &pack,
            KeyInputDynConf const &dynConf,
            LabelConfig const &label,
            KeyInputConfig const &keyInput = KeyInputFactory::getStandardConfig(),
            const KeyInputEventScript keyInputHandler = [](UNUSED const Engine::Entity &entity,
                                                            UNUSED const std::pair<const raylib::KeyBoard, string> &key) {
            });
        static KeyInputConfig getStandardConfig();
        static const std::map<raylib::KeyBoard, string> keyToStr;

      protected:
      private:
    };
} // namespace GUI

#endif /* !KEYINPUTFACTORY_HPP_ */
