/*
 * EPITECH PROJECT, 2021
 * IABomberman
 * File description:
 * IABomberman.cpp
 */

#include "IABomberman.hpp"

IABomberman::IABomberman(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
: IA::IACore<TileType, BombermanAction>(pos, env)
{

}

IABomberman::~IABomberman()
{

}