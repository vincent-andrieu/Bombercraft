/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 Chrono.cpp.cc
*/

#include "PlayerConfig.hpp"

using namespace Component;

Component::PlayerConfig::PlayerConfig(const PlayerID playerId, PlayerKeyBindings defaultKeyBinding)
    : _id(playerId), _keyBindings(defaultKeyBinding), _defaultKeyBinding(defaultKeyBinding)
{
}

PlayerConfig &PlayerConfig::operator=(const PlayerConfig &src)
{
    this->_id = src._id;
    this->_keyBindings = src._keyBindings;
    this->_defaultKeyBinding = src._defaultKeyBinding;

    return *this;
}

const uint &Component::PlayerConfig::getPlayerId() const
{
    return this->_id;
}

const PlayerKeyBindings &Component::PlayerConfig::getPlayerKeyBindings() const
{
    return this->_keyBindings;
}

const PlayerKeyBindings &PlayerConfig::getPlayerDefaultKeyBindings() const
{
    return this->_defaultKeyBinding;
}

void PlayerConfig::resetAllKeyBindings()
{
    this->_keyBindings = this->_defaultKeyBinding;
}

void PlayerConfig::setKeyMoveUp(const raylib::KeyBoard &key)
{
    this->_keyBindings.moveUp = key;
}

void PlayerConfig::setKeyMoveDown(const raylib::KeyBoard &key)
{
    this->_keyBindings.moveDown = key;
}

void PlayerConfig::setKeyMoveLeft(const raylib::KeyBoard &key)
{
    this->_keyBindings.moveLeft = key;
}

void PlayerConfig::setKeyMoveRight(const raylib::KeyBoard &key)
{
    this->_keyBindings.moveRight = key;
}

void PlayerConfig::setKeyPause(const raylib::KeyBoard &key)
{
    this->_keyBindings.pause = key;
}

void PlayerConfig::setKeyPlaceBomb(const raylib::KeyBoard &key)
{
    this->_keyBindings.placeBomb = key;
}