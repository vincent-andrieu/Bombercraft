/*
 * EPITECH PROJECT, 2021
 * IA
 * File description:
 * IACore.cpp
 */

#include "IACore.hpp"

using namespace IA;

template <typename TileType, typename Action>
IACore<TileType, Action>::IACore(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, unsigned int seed)
: _pos(pos), _prevPos(pos), _env(env), _isRunnable({0}), _seed(seed), _actLink({0}), _MovementFunc(nullptr)
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
    } else {
        throw IAExceptions("This tile is already set.", false);
    }
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::unsetRunnableTile(TileType tile)
{
    auto it = std::find(this->_isRunnable.begin(), this->_isRunnable.end(), tile);

    if (it != this->_isRunnable.end()) {
        this->_isRunnable.erase(it);
    } else {
        throw IAExceptions("This tile is not set.", false);
    }
}

template <typename TileType, typename Action>
Movement IACore<TileType, Action>::getIAMovement()
{
    Movement tmp;

    if (!this->_MovementQueue.size()) {
        if (!this->_MovementFunc)
            throw IAExceptions("Moving function not initialized", false);
        else
            this->_MovementFunc(this->_env, this->_pos, this->_MovementQueue);
    }
    if (!this->_MovementQueue.size())
        return Movement::IA_MOVE_NONE;
    tmp = this->_MovementQueue.front();
    this->_MovementQueue.pop();
    this->applyIAMovement(tmp);
    return tmp;
}

template <typename TileType, typename Action>
Action IACore<TileType, Action>::getIAAction() const
{
    for (auto it : this->_actLink) {
        if (it.second(this->_env, this->_pos))
            return it.first;
    }
    return static_cast<GameModule::BombermanAction>(0);
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setIAAction(Action act, std::function<bool(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos)> func)
{
    this->_actLink[act] = func;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setIAMovement(std::function<void(std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos, std::queue<IA::Movement> &list)> func)
{
    this->_MovementFunc = func;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::applyIAMovement(Movement move)
{
    this->_prevPos = this->_pos;
    switch (move)
    {
        case Movement::IA_MOVE_UP: this->_pos.second--; break;
        case Movement::IA_MOVE_NONE: ; break;
        case Movement::IA_MOVE_DOWN: this->_pos.second++; break;
        case Movement::IA_MOVE_LEFT: this->_pos.first--; break;
        case Movement::IA_MOVE_RIGHT: this->_pos.first++; break;
        default: throw IAExceptions("Invalide Move", false); break;
    }
}

template <typename TileType, typename Action>
unsigned int IACore<TileType, Action>::getSeed() const
{
    return this->_seed;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setSeed(unsigned int seed)
{
    this->_seed = seed;
}

template <typename TileType, typename Action>
void IACore<TileType, Action>::setEnemyPos(std::vector<std::pair<size_t, size_t>> enemy)
{
    this->_enemyPos = enemy;
}

template class IA::IACore<GameModule::TileType, GameModule::BombermanAction>;