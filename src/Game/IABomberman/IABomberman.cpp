/*
 * EPITECH PROJECT, 2021
 * IABomberman
 * File description:
 * IABomberman.cpp
 */

#include "IABomberman.hpp"

using namespace IA;

template <typename TileType, typename Action>
IABomberman<TileType, Action>::IABomberman()
{

}

template <typename TileType, typename Action>
IABomberman<TileType, Action>::~IABomberman()
{

}

template <typename TileType, typename Action>
void IABomberman<TileType, Action>::setIAEnv(std::vector<std::vector<TileType>> env)
{

}

template <typename TileType, typename Action>
std::vector<std::vector<TileType>> IABomberman<TileType, Action>::getIAEnv() const
{

}

template <typename TileType, typename Action>
void IABomberman<TileType, Action>::setIAPos(std::pair<size_t, size_t> pos)
{

}

template <typename TileType, typename Action>
std::pair<size_t, size_t> IABomberman<TileType, Action>::getIAPos() const
{

}

template <typename TileType, typename Action>
void IABomberman<TileType, Action>::setRunnableTile(TileType tile)
{

}

template <typename TileType, typename Action>
void IABomberman<TileType, Action>::unsetRunnableTile(TileType tile)
{

}

template <typename TileType, typename Action>
Movement IABomberman<TileType, Action>::getIAMovement() const
{

}

template <typename TileType, typename Action>
Action IABomberman<TileType, Action>::getIAAction() const
{

}

template <typename TileType, typename Action>
void IABomberman<TileType, Action>::setIAAction(Action act, std::function<bool(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func)
{

}

template class IABomberman<GameModule::TileType, BombermanAction>;