/*
 * EPITECH PROJECT, 2021
 * IABomberman
 * File description:
 * IABomberman.cpp
 */

#include "IABomberman.hpp"

using namespace GameModule;

IABomberman::IABomberman(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
    : IA::IACore<TileType, BombermanAction>(pos, env), _range(0), _defaultValue(-1), _randomMove(0), _randomBomb(7)
{
    // default value
    if (Game::CoreData::settings->isSetInFile("IA_INTERNAL_DEFAULT_VALUE"))
        this->_defaultValue = Game::CoreData::settings->getInt("IA_INTERNAL_DEFAULT_VALUE");
    else
        std::cerr << "Default_value: " << this->_defaultValue << std::endl;
    // range
    if (Game::CoreData::settings->isSetInFile("IA_EXPLOSION_RANGE"))
        this->_range = Game::CoreData::settings->getInt("IA_EXPLOSION_RANGE");
    else
        std::cerr << "Default range: " << this->_range << std::endl;
    // range
    if (Game::CoreData::settings->isSetInFile("IA_RANDOM_PROB"))
        this->_randomMove = Game::CoreData::settings->getInt("IA_RANDOM_PROB");
    else
        std::cerr << "Default %: " << this->_randomMove << std::endl;
    // random bombe
    if (Game::CoreData::settings->isSetInFile("IA_BOMB_PROB"))
        this->_randomBomb = Game::CoreData::settings->getInt("IA_BOMB_PROB");
    else
        std::cerr << "Default bombe prob: 1/" << this->_randomBomb << std::endl;
    if (this->_randomBomb <= 0)
        throw IAExceptions("\"IA_BOMB_PROB\" must be > 0");
    // SETINGS
    this->IASettings();
}

void IABomberman::IASettings()
{
    this->setIAAction(
        BombermanAction::ACTION_TRIGGER_BOMBE, [this](std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos) {
            return this->actionPutBomber(pos, env);
        });
    this->setIAMovement(
        [this](std::vector<std::vector<TileType>> env, std::pair<size_t, size_t> pos, std::queue<IA::Movement> &list) {
            return this->movementPrediction(pos, env, list);
        });
    this->setRunnableTile(TileType::TILE_EMPTY);
}

void IABomberman::setIAEnv(std::vector<std::vector<TileType>> env)
{
    for (size_t y = 0; y < env.size(); y++) {
        for (size_t x = 0; x < env[y].size(); x++) {
            if (env[y][x] == TileType::TILE_BOMB) {
                env = this->getMapWithExposionEffect(env, {x, y}, this->_range);
            }
        }
    }
    IACore::setIAEnv(env);
}

void IABomberman::setRandomMove(const size_t randomness)
{
    this->_randomMove = randomness;
}

void IABomberman::setRandomBomb(const size_t randomness)
{
    this->_randomBomb = randomness;
}

void IABomberman::setRange(size_t range)
{
    this->_range = range;
}

void IABomberman::setEnemyPos(std::vector<std::pair<size_t, size_t>> enemy)
{
    if (enemy.size() > 3)
        throw IAExceptions("Invalide list size: " + std::to_string(enemy.size()), true);
    IACore::setEnemyPos(enemy);
}

std::vector<std::pair<size_t, size_t>> IABomberman::getAvailableTile(
    const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env) const
{
    size_t x = pos.first;
    size_t y = pos.second;
    std::vector<std::pair<size_t, size_t>> valueOk;

    if (x != 0 && env[y][x - 1] == TileType::TILE_EMPTY)
        valueOk.push_back({x - 1, y});
    if (y != 0 && env[y - 1][x] == TileType::TILE_EMPTY)
        valueOk.push_back({x, y - 1});
    if (x + 1 < env[y].size() && env[y][x + 1] == TileType::TILE_EMPTY)
        valueOk.push_back({x + 1, y});
    if (y + 1 < env.size() && env[y + 1][x] == TileType::TILE_EMPTY)
        valueOk.push_back({x, y + 1});
    return valueOk;
}

raylib::MyVector3 IABomberman::findOrientation(const std::pair<size_t, size_t> &pos, const std::pair<size_t, size_t> &bomb) const
{
    if (pos.first + 1 == bomb.first && pos.second == bomb.second) {
        return {0, 270, 0};
    }
    if (pos.first == bomb.first && pos.second - 1 == bomb.second) {
        return {0, 180, 0};
    }
    if (pos.first - 1 == bomb.first && pos.second == bomb.second) {
        return {0, 90, 0};
    }
    return {0, 0, 0};
}

bool IABomberman::actionPutBomber(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
{
    std::queue<IA::Movement> list;
    std::vector<std::vector<TileType>> editedEnv;
    std::vector<std::pair<size_t, size_t>> available;

    if (!this->isSecurePlace(env[pos.second][pos.first]))
        return false;

    int tmp = std::rand() % this->_randomBomb;
    if (tmp)
        return false;
    available = this->getAvailableTile(pos, env);
    for (size_t i = 0; i < available.size(); i++) {
        editedEnv = this->getMapWithExposionEffect(env, available[i], this->_range);
        if (isCorrectBomb(available[i]) && this->findSecurePlace(pos, editedEnv, list)) {
            this->_MovementQueue = list;
            this->_orentation = this->findOrientation(pos, available[i]);
            return true;
        }
    }
    return false;
}

void IABomberman::movementPrediction(
    std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list)
{
    size_t x = pos.first;
    size_t y = pos.second;

    if (this->isRandomMove()) {
        this->randomMove(pos, env, list);
    } else if (this->isSecurePlace(env[y][x])) {
        this->offensiveMove(pos, env, list);
    } else {
        if (!this->findSecurePlace(pos, env, list)) {
            std::cerr << "RIP mon ruf" << std::endl;
            this->clearQueue(list);
        }
    }
}

bool IABomberman::findSecurePlace(
    std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list)
{
    bool stat = false;
    std::vector<std::vector<int>> cost_array = this->getCostArray(pos, env);
    std::pair<size_t, size_t> secure_place = this->getCostLessSafeMove(cost_array, env, stat);

    if (!stat) {
        cost_array = this->getCostArray(pos, env);
        secure_place = this->getCostLessSafeMove(cost_array, env, stat);
    }
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
    if (type == TileType::TILE_EXPLOSION || type == TileType::TILE_BOMB || type == TileType::TILE_DANGER)
        return false;
    return true;
}

std::vector<std::vector<int>> IABomberman::getCostArray(
    const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env) const
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
    cpy[pos.second][pos.first] = 0;
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

std::pair<size_t, size_t> IABomberman::getCostLessSafeMove(
    const std::vector<std::vector<int>> &tab, const std::vector<std::vector<TileType>> &env, bool &stat) const
{
    int best_value = -1;
    std::pair<size_t, size_t> best = {-1, -1};

    stat = false;
    for (size_t y = 0; y < tab.size(); y++) {
        for (size_t x = 0; x < tab[y].size(); x++) {
            if (tab[y][x] != this->_defaultValue && this->isSecurePlace(env[y][x])
                && (best_value > tab[y][x] || best_value == -1)) {
                stat = true;
                best = {x, y};
                best_value = tab[y][x];
            }
        }
    }
    return best;
}

void IABomberman::loadPath(
    const std::vector<std::vector<int>> &tab, std::pair<size_t, size_t> end, std::queue<IA::Movement> &list) const
{
    IA::Movement toPush;
    size_t x = end.first;
    size_t y = end.second;
    int goal = tab[y][x] - 1;
    std::pair<size_t, size_t> next;

    if (!tab[y][x])
        return;
    if (goal < 0)
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

std::vector<std::vector<TileType>> IABomberman::getMapWithExposionEffect(
    std::vector<std::vector<TileType>> env, const std::pair<size_t, size_t> &pos, size_t range) const
{
    int move = 1;
    size_t x = pos.first;
    size_t y = pos.second;
    int tmp;

    if (env[y][x] != TileType::TILE_BOMB)
        return env;
    for (size_t i = 0; i < range; i++) {
        tmp = (int) (x + 1 + (i * move));
        if (tmp >= 0 && x + (i * move) < env[y].size()) {
            if (env[y][tmp] == TileType::TILE_EMPTY || env[y][tmp] == TileType::TILE_BONUS || env[y][tmp] == TileType::TILE_EXPLOSION || env[y][tmp] == TileType::TILE_DANGER) {
                if (env[y][tmp] != TileType::TILE_EXPLOSION)
                    env[y][tmp] = TileType::TILE_DANGER;
            }
            else
                break;
        }
    }
    for (size_t i = 0; i < range; i++) {
        tmp = (int) (y + 1 + (i * move));
        if (tmp >= 0 && y + (i * move) < env.size()) {
            if (env[tmp][x] == TileType::TILE_EMPTY || env[tmp][x] == TileType::TILE_BONUS || env[tmp][x] == TileType::TILE_EXPLOSION || env[tmp][x] == TileType::TILE_DANGER) {
                if (env[tmp][x] != TileType::TILE_EXPLOSION)
                    env[tmp][x] = TileType::TILE_DANGER;
            }
            else
                break;
        }
    }
    move = -1;
    for (size_t i = 0; i < range; i++) {
        tmp = (int) (x - 1 + (i * move));
        if (tmp > 0 && x + (i * move) < env[y].size()) {
            if (env[y][tmp] == TileType::TILE_EMPTY || env[y][tmp] == TileType::TILE_BONUS || env[y][tmp] == TileType::TILE_EXPLOSION || env[y][tmp] == TileType::TILE_DANGER) {
                if (env[y][tmp] != TileType::TILE_EXPLOSION)
                    env[y][tmp] = TileType::TILE_DANGER;
            }
            else
                break;
        }
    }
    for (size_t i = 0; i < range; i++) {
        tmp = (int) (y - 1 + (i * move));
        if (tmp > 0 && y + (i * move) < env.size()) {
            if (env[tmp][x] == TileType::TILE_EMPTY || env[tmp][x] == TileType::TILE_BONUS || env[tmp][x] == TileType::TILE_EXPLOSION || env[tmp][x] == TileType::TILE_DANGER) {
                if (env[tmp][x] != TileType::TILE_EXPLOSION)
                    env[tmp][x] = TileType::TILE_DANGER;
            }
            else
                break;
        }
    }
    return env;
}

IA::Movement IABomberman::getIAMovement()
{
    std::pair<size_t, size_t> nextPos;
    IA::Movement tmp;

    if (this->_env[this->_pos.second][this->_pos.first] == TileType::TILE_DANGER)
        this->setRunnableTile(TileType::TILE_DANGER);
    if (this->isStuck()) {
        this->clearQueue(this->_MovementQueue);
        this->randomMove(this->_pos, this->_env, this->_MovementQueue);
    }
    tmp = IACore::getIAMovement();
    nextPos = this->getNextPos(tmp);
    if (this->isSecurePlace(this->_env[this->_pos.second][this->_pos.first])
        && !this->isSecurePlace(this->_env[nextPos.second][nextPos.first])) {
        this->clearQueue(this->_MovementQueue);
        std::cerr << "On a encore eu de la chance" << std::endl;
        if (this->_env[this->_pos.second][this->_pos.first] == TileType::TILE_DANGER)
            this->unsetRunnableTile(TileType::TILE_DANGER);
        return IA::Movement::IA_MOVE_NONE;
    }
    this->_prevPos = this->_pos;
    if (this->_env[this->_pos.second][this->_pos.first] == TileType::TILE_DANGER)
        this->unsetRunnableTile(TileType::TILE_DANGER);
    return tmp;
}

void IABomberman::randomMove(
    const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env, std::queue<IA::Movement> &list)
{
    size_t x = pos.first;
    size_t y = pos.second;
    IA::Movement toPush;
    std::vector<IA::Movement> valueOk;

    if (x != 0 && this->isRunnable(env[y][x - 1]))
        valueOk.push_back(IA::Movement::IA_MOVE_LEFT);
    if (y != 0 && this->isRunnable(env[y - 1][x]))
        valueOk.push_back(IA::Movement::IA_MOVE_UP);
    if (x + 1 < env[y].size() && this->isRunnable(env[y][x + 1]))
        valueOk.push_back(IA::Movement::IA_MOVE_RIGHT);
    if (y + 1 < env.size() && this->isRunnable(env[y + 1][x]))
        valueOk.push_back(IA::Movement::IA_MOVE_DOWN);
    this->clearQueue(list);
    if (valueOk.size()) {
        toPush = valueOk[std::rand() % valueOk.size()];
    } else {
        toPush = IA::Movement::IA_MOVE_NONE;
    }
    list.push(toPush);
}

void IABomberman::offensiveMove(
    const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env, std::queue<IA::Movement> &list)
{
    std::queue<IA::Movement> path;
    std::vector<std::vector<int>> cost;

    if (this->_enemyPos.size() > 3)
        throw IAExceptions("Invalide enemy list", true);
    cost = this->findEnemy(pos, env);
    for (size_t i = 0; i < this->_enemyPos.size(); i++) {
        if (cost[this->_enemyPos[i].second][this->_enemyPos[i].first] != this->_defaultValue) {
            this->clearQueue(list);
            this->loadPath(cost, this->_enemyPos[i], path);
            if (path.size())
                list.push(path.front());
            else
                this->randomMove(pos, env, list);
            this->clearQueue(path);
            return;
        }
    }
    if (!this->_enemyPos.size()) {
        this->clearQueue(list);
        list.push(IA::Movement::IA_MOVE_NONE);
    }
    this->attackBusy(pos, env, list);
}

bool IABomberman::isRandomMove() const
{
    size_t randomProba = this->_randomMove;

    if (!randomProba)
        return false;
    if ((size_t) (std::rand() % 100) <= randomProba)
        return true;
    return false;
}

std::vector<std::vector<int>> IABomberman::findEnemy(
    const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env) const
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
    cpy[pos.second][pos.first] = 0;
    while (stat) {
        stat = false;
        for (size_t y = 0; y < cpy.size(); y++) {
            for (size_t x = 0; x < cpy[y].size(); x++) {
                if (cpy[y][x] == to_find) {
                    stat = true;
                    if (x + 1 < cpy[y].size() && cpy[y][x + 1] == this->_defaultValue && this->isRunnable(env[y][x + 1]))
                        cpy[y][x + 1] = to_find + 1;
                    if (y + 1 < cpy.size() && cpy[y + 1][x] == this->_defaultValue && this->isRunnable(env[y + 1][x]))
                        cpy[y + 1][x] = to_find + 1;
                    if (x != 0 && cpy[y][x - 1] == this->_defaultValue && this->isRunnable(env[y][x - 1]))
                        cpy[y][x - 1] = to_find + 1;
                    if (y != 0 && cpy[y - 1][x] == this->_defaultValue && this->isRunnable(env[y - 1][x]))
                        cpy[y - 1][x] = to_find + 1;
                }
            }
        }
        to_find++;
    }
    return cpy;
}

bool IABomberman::isStuck() const
{
    return this->_pos == this->_prevPos;
}

std::pair<size_t, size_t> IABomberman::getNextPos(IA::Movement move) const
{
    std::pair<size_t, size_t> pos = this->_pos;

    switch (move) {
        case IA::Movement::IA_MOVE_UP: pos.second--; break;
        case IA::Movement::IA_MOVE_NONE:; break;
        case IA::Movement::IA_MOVE_DOWN: pos.second++; break;
        case IA::Movement::IA_MOVE_LEFT: pos.first--; break;
        case IA::Movement::IA_MOVE_RIGHT: pos.first++; break;
        default: throw IAExceptions("Invalide Move", false); break;
    }
    return pos;
}

bool IABomberman::isCorrectBomb(const std::pair<size_t, size_t> &pos) const
{
    if (pos.first + 1 < this->_env[pos.second].size() && this->_env[pos.second][pos.first + 1] == TileType::TILE_SOFT)
        return true;
    if (pos.second + 1 < this->_env.size() && this->_env[pos.second + 1][pos.first] == TileType::TILE_SOFT)
        return true;
    if (pos.first && this->_env[pos.second][pos.first - 1] == TileType::TILE_SOFT)
        return true;
    if (pos.second && this->_env[pos.second - 1][pos.first] == TileType::TILE_SOFT)
        return true;

    if (pos.first + 1 < this->_env[pos.second].size() && this->isEnemy({pos.second, pos.first + 1}))
        return true;
    if (pos.second + 1 < this->_env.size() && this->isEnemy({pos.second + 1, pos.first}))
        return true;
    if (pos.first && this->isEnemy({pos.second, pos.first - 1}))
        return true;
    if (pos.second && this->isEnemy({pos.second - 1, pos.first}))
        return true;
    return false;
}

raylib::MyVector3 IABomberman::getOrientation() const
{
    return this->_orentation;
}

bool IABomberman::isEnemy(const std::pair<size_t, size_t> &pos) const
{
    auto it = std::find(this->_enemyPos.begin(), this->_enemyPos.end(), pos);

    if (it == this->_enemyPos.end())
        return false;
    return true;
}

void IABomberman::attackBusy(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env, std::queue<IA::Movement> &list)
{
    this->randomMove(pos, env, list);
}