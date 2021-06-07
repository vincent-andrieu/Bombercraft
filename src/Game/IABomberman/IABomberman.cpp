/*
 * EPITECH PROJECT, 2021
 * IABomberman
 * File description:
 * IABomberman.cpp
 */

#include "IABomberman.hpp"

using namespace GameModule;

IABomberman::IABomberman(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
: IA::IACore<TileType, BombermanAction>(pos, env)
{
    this->setIAAction(BombermanAction::ACTION_TRIGGER_BOMBE, [this](std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos) {
        return this->actionPutBomber(pos, env);
    });
}

IABomberman::~IABomberman()
{

}

bool IABomberman::actionPutBomber(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
{
    // TODO to dev
    (void) pos;
    (void) env;
    return false;
}