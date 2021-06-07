/*
 * EPITECH PROJECT, 2021
 * IABomberman
 * File description:
 * IABomberman.cpp
 */

#include "IABomberman.hpp"

using namespace GameModule;

IABomberman::IABomberman(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, size_t range, int defaultValue)
: IA::IACore<TileType, BombermanAction>(pos, env), _range(range), _defaultValue(defaultValue)
{
    this->setIAAction(BombermanAction::ACTION_TRIGGER_BOMBE, [this](std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos) {
        return this->actionPutBomber(pos, env);
    });
    this->setIAMovement([this](std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos, std::queue<IA::Movement> &list) {
        return this->movementPrediction(pos, env, list);
    });
    this->setRunnableTile(TileType::TILE_BONUS);
    this->setRunnableTile(TileType::TILE_EMPTY);
}

IABomberman::~IABomberman()
{
}

void IABomberman::setRange(size_t range)
{
    this->_range = range;
}

bool IABomberman::actionPutBomber(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
{
    std::queue<IA::Movement> list;
    std::vector<std::vector<TileType>> editedEnv = this->getMapWithExposionEffect(env, pos, this->_range);
    
    if (this->findSecurePlace(pos, env, list))
        return false;
    this->_MovementQueue = list;
    return true;
}

void IABomberman::movementPrediction(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list)
{
    size_t x = pos.first;
    size_t y = pos.second;

    if (this->isRandomMove()) {
        this->randomMove(pos, env, list);
    } else if (this->isSecurePlace(env[y][x])) {
        this->offensiveMove(pos, env, list);
    } else {
        if (!this->findSecurePlace(pos, env, list))
            std::cout << "RIP mon ruf" << std::endl;
    }
}

bool IABomberman::findSecurePlace(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list)
{
    bool stat = false;
    std::vector<std::vector<int>> cost_array = this->getCostArray(pos, env);
    std::pair<size_t, size_t> secure_place = this->getCostLessSafeMove(cost_array, env, stat);

    if (!stat)
        return false;
    this->clearQueue(list);
    loadPath(cost_array, secure_place, list);
    return true;
}

void IABomberman::clearQueue(std::queue<IA::Movement> &list)
{
    while (list.size())
        list.pop();
}

bool IABomberman::isRunnable(TileType type) const
{
    for (auto it : this->_isRunnable)
        if (it == type)
            return true;
    return false;
}

bool IABomberman::isSecurePlace(TileType type) const
{
    if (type == TileType::TILE_EXPLOSION)
        return false;
    return true;
}

std::vector<std::vector<int>> IABomberman::getCostArray(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env) const
{
    bool stat = true;
    int to_find = 0;
    std::vector<std::vector<int>> cpy;
    std::vector<int> cpy_tmp;

    for (size_t y = 0; y < env.size(); y++) {
        cpy_tmp.clear();
        for (size_t x = 0; x < env[y].size(); x++) {
            cpy_tmp.push_back(this->_defaultValue);
        }
        cpy.push_back(cpy_tmp);
    }
    cpy[pos.first][pos.second] = 0;
    while (stat) {
        stat = false;
        for (size_t y = 0; y < cpy.size(); y++) {
            for (size_t x = 0; x < cpy[y].size(); x++) {
                if (cpy[y][x] == to_find) {
                    stat = true;
                    if (x + 1 < cpy[y].size() && cpy[y][x + 1] == this->_defaultValue && isRunnable(env[y][x + 1]))
                        cpy[y][x + 1] = to_find + 1;
                    if (y + 1 < cpy.size() && cpy[y + 1][x] == this->_defaultValue && isRunnable(env[y + 1][x]))
                        cpy[y + 1][x] = to_find + 1;
                    if (x != 0 && cpy[y][x - 1] == this->_defaultValue && isRunnable(env[y][x - 1]))
                        cpy[y][x - 1] = to_find + 1;
                    if (y != 0 && cpy[y - 1][x] == this->_defaultValue && isRunnable(env[y - 1][x]))
                        cpy[y - 1][x] = to_find + 1;
                }
            }
        }
        to_find++;
    }
    return cpy;
}

std::pair<size_t, size_t> IABomberman::getCostLessSafeMove(const std::vector<std::vector<int>> &tab, const std::vector<std::vector<TileType>> &env, bool &stat) const
{
    int best_value = -1;
    std::pair<size_t, size_t> best = {-1, -1};

    stat = false;
    for (size_t y = 0; y < tab.size(); y++) {
        for (size_t x = 0; x < tab[y].size(); x++) {
            if (tab[y][x] != this->_defaultValue && this->isSecurePlace(env[y][x]) && (best_value > tab[y][x] || best_value == -1)) {
                stat = true;
                best = {x, y};
                best_value = tab[y][x];
            }
        }
    }
    return best;
}

void IABomberman::loadPath(const std::vector<std::vector<int>> &tab, std::pair<size_t, size_t> end, std::queue<IA::Movement> &list) const
{
    IA::Movement toPush;
    size_t x = end.first;
    size_t y = end.second;
    int goal = tab[y][x] - 1;
    std::pair<size_t, size_t> next;

    if (!tab[y][x])
        return;
    if (x != 0 && tab[y][x - 1] == goal) {
        next = {x - 1, y};
        toPush = IA::Movement::IA_MOVE_RIGHT;
    } else if (y != 0 && tab[y - 1][x] == goal) {
        next = {x, y - 1};
        toPush = IA::Movement::IA_MOVE_DOWN;
    } else if (x + 1 < tab[y].size() && tab[y][x + 1] == goal) {
        next = {x + 1, y};
        toPush = IA::Movement::IA_MOVE_LEFT;
    } else if (y + 1 < tab.size() && tab[y + 1][x] == goal) {
        next = {x, y + 1};
        toPush = IA::Movement::IA_MOVE_UP;
    } else {
        throw IAExceptions("Incorrect parameters.", true);
    }
    this->loadPath(tab, next, list);
    list.push(toPush);
}

std::vector<std::vector<TileType>> IABomberman::getMapWithExposionEffect(std::vector<std::vector<TileType>> env, const std::pair<size_t, size_t> &pos, size_t range) const
{
    int move = 1;
    size_t x = pos.first;
    size_t y = pos.second;
    int tmp;

    for (size_t i = 0; i < range; i++) {
        tmp = x + (i * move);
        if (tmp >= 0 && x + (i * move) < env[y].size()) {
            if (env[y][tmp] == TileType::TILE_EMPTY || env[y][tmp] == TileType::TILE_BONUS)
                env[y][tmp] = TileType::TILE_EXPLOSION;
            else if (env[y][tmp] == TileType::TILE_SOFT) {
                env[y][tmp] = TileType::TILE_EXPLOSION;
                break;
            } else if (env[y][tmp] == TileType::TILE_HARD) {
                break;
            }
        }
    }
    for (size_t i = 0; i < range; i++) {
        tmp = y + (i * move);
        if (tmp >= 0 && y + (i * move) < env.size()) {
            if (env[tmp][x] == TileType::TILE_EMPTY || env[tmp][x] == TileType::TILE_BONUS)
                env[tmp][x] = TileType::TILE_EXPLOSION;
            else if (env[tmp][x] == TileType::TILE_SOFT) {
                env[tmp][x] = TileType::TILE_EXPLOSION;
                break;
            } else if (env[tmp][x] == TileType::TILE_HARD) {
                break;
            }
        }
    }
    move = -1;
    for (size_t i = 0; i < range; i++) {
        tmp = x + (i * move);
        if (tmp >= 0 && x + (i * move) < env[y].size()) {
            if (env[y][tmp] == TileType::TILE_EMPTY || env[y][tmp] == TileType::TILE_BONUS)
                env[y][tmp] = TileType::TILE_EXPLOSION;
            else if (env[y][tmp] == TileType::TILE_SOFT) {
                env[y][tmp] = TileType::TILE_EXPLOSION;
                break;
            } else if (env[y][tmp] == TileType::TILE_HARD) {
                break;
            }
        }
    }
    for (size_t i = 0; i < range; i++) {
        tmp = y + (i * move);
        if (tmp >= 0 && y + (i * move) < env.size()) {
            if (env[tmp][x] == TileType::TILE_EMPTY || env[tmp][x] == TileType::TILE_BONUS)
                env[tmp][x] = TileType::TILE_EXPLOSION;
            else if (env[tmp][x] == TileType::TILE_SOFT) {
                env[tmp][x] = TileType::TILE_EXPLOSION;
                break;
            } else if (env[tmp][x] == TileType::TILE_HARD) {
                break;
            }
        }
    }
    return env;
}

IA::Movement IABomberman::getIAMovement()
{
    IA::Movement tmp = IACore::getIAMovement();

    if (this->_prevPos.first != -1 && this->_prevPos.second != -1)
        if (this->isSecurePlace(this->_env[this->_prevPos.first][this->_prevPos.second])
        && !this->isSecurePlace(this->_env[this->_pos.first][this->_pos.second])) {
            this->clearQueue(this->_MovementQueue);
            this->_pos = this->_prevPos;
            std::cout << "On a encore eu de la chance" << std::endl;
            return IA::Movement::IA_MOVE_NONE;
        }
    return tmp;
}

void IABomberman::randomMove(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env, std::queue<IA::Movement> &list)
{
    // TODO ADD RANDOMMOVE
    (void) pos;
    (void) env;
    this->clearQueue(list);
    list.push(IA::Movement::IA_MOVE_NONE);
}

void IABomberman::offensiveMove(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env, std::queue<IA::Movement> &list)
{
    // TODO ADD OFFENSIVE ACT
    (void) pos;
    (void) env;
    this->clearQueue(list);
    list.push(IA::Movement::IA_MOVE_NONE);
}

bool IABomberman::isRandomMove() const
{
    // TODO ADD PROBA FOR RANDOMMOVE
    return false;
}