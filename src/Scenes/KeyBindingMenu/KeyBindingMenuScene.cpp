/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 03/06/2021 DebugScene.cpp.cc
*/

#include "KeyBindingMenuScene.hpp"
#include "GUI/Factories/Button/ButtonFactory.hpp"
#include "GUI/Factories/Label/LabelFactory.hpp"

using namespace Game;
using namespace raylib;

KeyBindingMenuScene::KeyBindingMenuScene(Engine::SystemManager &systemManager)
    : AbstractScene(systemManager, *Game::CoreData::entityManager)
{
    this->usersKeyBindings[0].moveUp = CONF_GET_KEYBINDING("PLAYER_ONE_MOVE_UP");
    this->usersKeyBindings[0].moveDown = CONF_GET_KEYBINDING("PLAYER_ONE_MOVE_DOWN");
    this->usersKeyBindings[0].moveLeft = CONF_GET_KEYBINDING("PLAYER_ONE_MOVE_LEFT");
    this->usersKeyBindings[0].moveRight = CONF_GET_KEYBINDING("PLAYER_ONE_MOVE_RIGHT");
    this->usersKeyBindings[0].pause = CONF_GET_KEYBINDING("PLAYER_ONE_MOVE_PAUSE");
    this->usersKeyBindings[0].placeBomb = CONF_GET_KEYBINDING("PLAYER_ONE_MOVE_PLACE_BOMB");

    this->usersKeyBindings[1].moveUp = CONF_GET_KEYBINDING("PLAYER_TWO_MOVE_UP");
    this->usersKeyBindings[1].moveDown = CONF_GET_KEYBINDING("PLAYER_TWO_MOVE_DOWN");
    this->usersKeyBindings[1].moveLeft = CONF_GET_KEYBINDING("PLAYER_TWO_MOVE_LEFT");
    this->usersKeyBindings[1].moveRight = CONF_GET_KEYBINDING("PLAYER_TWO_MOVE_RIGHT");
    this->usersKeyBindings[1].pause = CONF_GET_KEYBINDING("PLAYER_TWO_MOVE_PAUSE");
    this->usersKeyBindings[1].placeBomb = CONF_GET_KEYBINDING("PLAYER_TWO_MOVE_PLACE_BOMB");

    this->usersKeyBindings[2].moveUp = CONF_GET_KEYBINDING("PLAYER_THREE_MOVE_UP");
    this->usersKeyBindings[2].moveDown = CONF_GET_KEYBINDING("PLAYER_THREE_MOVE_DOWN");
    this->usersKeyBindings[2].moveLeft = CONF_GET_KEYBINDING("PLAYER_THREE_MOVE_LEFT");
    this->usersKeyBindings[2].moveRight = CONF_GET_KEYBINDING("PLAYER_THREE_MOVE_RIGHT");
    this->usersKeyBindings[2].pause = CONF_GET_KEYBINDING("PLAYER_THREE_MOVE_PAUSE");
    this->usersKeyBindings[2].placeBomb = CONF_GET_KEYBINDING("PLAYER_THREE_MOVE_PLACE_BOMB");

    this->usersKeyBindings[3].moveUp = CONF_GET_KEYBINDING("PLAYER_FOUR_MOVE_UP");
    this->usersKeyBindings[3].moveDown = CONF_GET_KEYBINDING("PLAYER_FOUR_MOVE_DOWN");
    this->usersKeyBindings[3].moveLeft = CONF_GET_KEYBINDING("PLAYER_FOUR_MOVE_LEFT");
    this->usersKeyBindings[3].moveRight = CONF_GET_KEYBINDING("PLAYER_FOUR_MOVE_RIGHT");
    this->usersKeyBindings[3].pause = CONF_GET_KEYBINDING("PLAYER_FOUR_MOVE_PAUSE");
    this->usersKeyBindings[3].placeBomb = CONF_GET_KEYBINDING("PLAYER_FOUR_MOVE_PLACE_BOMB");
}

void KeyBindingMenuScene::open()
{
    GUI::LabelConfig labelConfig = GUI::LabelFactory::create(this->localEntities,
        MyVector2(CoreData::settings->getMyVector2("WIN_SIZE").a / 2 - 10, 50),
        "Controls",
        {
            CoreData::settings->getInt("DEF_FONT_SIZE"),
            raylib::RColor::RWHITE,
            CoreData::settings->getInt("DEF_FONT"),
        });
}

void KeyBindingMenuScene::update()
{
}