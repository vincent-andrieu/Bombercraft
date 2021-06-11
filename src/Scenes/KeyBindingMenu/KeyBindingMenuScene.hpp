/*
 * EPITECH PROJECT, 2021
 * KeyBindingMenu
 * File description:
 * KeyBindingMenuScene.hpp - Created: 11/06/2021
 */

#ifndef KEY_BINDING_MENU_SCENE_HPP
#define KEY_BINDING_MENU_SCENE_HPP

#include "GameEngine.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Systems/PlayerConfig/PlayerConfigSystem.hpp"
#include "Scenes/SceneWithEvents/SceneWithEvents.hpp"

#define CONF_GET_KEYBINDING(name) static_cast<raylib::KeyBoard>(Game::CoreData::settings->getInt(name))

namespace Game
{
    // static const std::array<KeyBindings, MAX_PLAYERS> defaultKeyBindings{{
    //     {
    //         raylib::KeyBoard::IKEY_Z,
    //         raylib::KeyBoard::IKEY_S,
    //         raylib::KeyBoard::IKEY_Q,
    //         raylib::KeyBoard::IKEY_D,
    //         raylib::KeyBoard::IKEY_W,
    //         raylib::KeyBoard::IKEY_L_ALT,
    //     },
    //     {
    //         raylib::KeyBoard::IKEY_UP,
    //         raylib::KeyBoard::IKEY_DOWN,
    //         raylib::KeyBoard::IKEY_LEFT,
    //         raylib::KeyBoard::IKEY_RIGHT,
    //         raylib::KeyBoard::IKEY_END,
    //         raylib::KeyBoard::IKEY_R_SHIFT,
    //     },
    //     {
    //         raylib::KeyBoard::IKEY_O,
    //         raylib::KeyBoard::IKEY_L,
    //         raylib::KeyBoard::IKEY_K,
    //         raylib::KeyBoard::IKEY_M,
    //         raylib::KeyBoard::IKEY_P,
    //         raylib::KeyBoard::IKEY_SPACE,
    //     },
    //     {
    //         raylib::KeyBoard::IKEY_KP_8,
    //         raylib::KeyBoard::IKEY_KP_2,
    //         raylib::KeyBoard::IKEY_KP_4,
    //         raylib::KeyBoard::IKEY_KP_6,
    //         raylib::KeyBoard::IKEY_KP_0,
    //         raylib::KeyBoard::IKEY_KP_5,
    //     },
    // }};

    class KeyBindingMenuScene : public Engine::AbstractScene, public SceneWithEvents {
      public:
        KeyBindingMenuScene(Engine::SystemManager &systemManager);
        ~KeyBindingMenuScene() = default;

        void open() override;

        void update() override;

      private:
        string _playerNumberTitle;
        Component::PlayerConfig *_selectedPlayer;
    };
} // namespace Game

#endif // DEBUGSCENE_HPP
