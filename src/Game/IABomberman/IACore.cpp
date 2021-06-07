/*
 * EPITECH PROJECT, 2021
 * IA
 * File description:
 * IACore.cpp
 */

#include "IACore.hpp"

using namespace IA;

template <typename TileType, typename Action>
IACore<TileType, Action>::IACore(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
: _pos(pos), _env(env), _actLink({0}), _isRunnable({0}), _MovementFunc(nullptr)
{
}

template <typename TileType, typename Action>
IACore<TileType, Action>::~IACore()
{
    this->_env.clear();
    this->_actLink.clear();
    this->_isRunnable.clear();
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setIAEnv(std::vector<std::vector<TileType>> env)
{
    this->_env = env;
}

template <typename TileType, typename Action>
std::vector<std::vector<TileType>> IACore<TileType, Action>::getIAEnv() const
{
    return this->_env;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setIAPos(std::pair<size_t, size_t> pos)
{
    this->_pos = pos;
}

template <typename TileType, typename Action>
std::pair<size_t, size_t> IACore<TileType, Action>::getIAPos() const
{
    return this->_pos;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setRunnableTile(TileType tile)
{
    auto it = std::find(this->_isRunnable.begin(), this->_isRunnable.end(), tile);

    if (it == this->_isRunnable.end()) {
        this->_isRunnable.push_back(tile);
    }
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::unsetRunnableTile(TileType tile)
{
    auto it = std::find(this->_isRunnable.begin(), this->_isRunnable.end(), tile);

    if (it != this->_isRunnable.end()) {
        this->_isRunnable.erase(it);
    }
}

template <typename TileType, typename Action>
Movement IACore<TileType, Action>::getIAMovement() const
{
    if (!this->_MovementFunc)
        throw std::invalid_argument("Moving function not initialized");
    return this->_MovementFunc(this->_env, this->_pos);
}

template <typename TileType, typename Action>
Action IACore<TileType, Action>::getIAAction() const
{
    for (auto it : this->_actLink) {
        if (it.second(this->_env, this->_pos))
            return it.first;
    }
    
    return GameModule::BombermanAction::ACTION_NONE;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setIAAction(Action act, std::function<bool(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func)
{
    this->_actLink[act] = func;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setIAMovement(std::function<Movement(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func)
{
    this->_MovementFunc = func;
}

template class IACore<GameModule::TileType, GameModule::BombermanAction>;