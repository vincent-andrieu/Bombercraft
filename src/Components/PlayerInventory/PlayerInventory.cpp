/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 PlayerInventory.cpp.cc
*/

#include "PlayerInventory.hpp"

using namespace Component;

PlayerInventory::PlayerInventory(const PlayerID playerId, PlayerInventoryInfo defaultInfo, PlayerConfig &config)
    : _id(playerId), _info(defaultInfo), _defaultInfo(defaultInfo)
{
    this->_info.config = &config;
}

PlayerInventory &PlayerInventory::operator=(const PlayerInventory &src)
{
    this->_id = src._id;
    this->_info = src._info;
    this->_defaultInfo = src._defaultInfo;

    return *this;
}

const PlayerID &Component::PlayerInventory::getPlayerId() const
{
    return this->_id;
}

const PlayerInventoryInfo &Component::PlayerInventory::getPlayerInventoryInfo() const
{
    return this->_info;
}

const PlayerInventoryInfo &PlayerInventory::getDefaultPlayerInventoryInfo() const
{
    return this->_defaultInfo;
}

void PlayerInventory::resetAllInfo()
{
    this->_info = this->_defaultInfo;
}

void PlayerInventory::setBomb(const size_t &bomb)
{
    this->_info.bomb = bomb;
}

void PlayerInventory::setSpeed(double speed)
{
    this->_info.speed = speed;
}

void PlayerInventory::setWallPass(const bool &wallPass)
{
    this->_info.wallPass = wallPass;
}

void PlayerInventory::setBlastRadius(const size_t &blastRadius)
{
    this->_info.blastRadius = blastRadius;
}

