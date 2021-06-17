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
    // seed
    if (Game::CoreData::settings->isSetInFile("IA_SEED"))
        this->setSeed(Game::CoreData::settings->getInt("IA_SEED"));
    else
        std::cerr << "Random seed" << std::endl;
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
    this->setRunnableTile(TileType::TILE_EXPLOSION);
    this->setRunnableTile(TileType::TILE_BONUS);
    this->setRunnableTile(TileType::TILE_EMPTY);
    this->setRunnableTile(TileType::TILE_BOMB);
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

bool IABomberman::actionPutBomber(std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env)
{
    std::queue<IA::Movement> list;
    std::vector<std::vector<TileType>> editedEnv;

    if (!this->isSecurePlace(env[pos.second][pos.first]))
        return false;
    int tmp = std::rand() % this->_randomBomb;
    if (tmp)
        return false;
    editedEnv = this->getMapWithExposionEffect(env, pos, this->_range);
    if (!this->findSecurePlace(pos, editedEnv, list))
        return false;
    this->_MovementQueue = list;
    return true;
}

void IABomberman::movementPrediction(
    std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list)
{
    size_t x = pos.first;
    size_t y = pos.second;

    if (this->isRandomMove()) {
        std::cout << "random move" << std::endl;
        this->randomMove(pos, env, list);
    } else if (this->isSecurePlace(env[y][x])) {
        std::cout << "offensive move" << std::endl;
        this->offensiveMove(pos, env, list);
    } else {
        std::cout << "findsecureplace move" << std::endl;
        if (!this->findSecurePlace(pos, env, list))
            std::cerr << "RIP mon ruf" << std::endl;
    }
}

bool IABomberman::findSecurePlace(
    std::pair<size_t, size_t> pos, std::vector<std::vector<TileType>> env, std::queue<IA::Movement> &list)
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
    if (type == TileType::TILE_EXPLOSION || type == TileType::TILE_BOMB)
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

    for (size_t i = 0; i < range; i++) {
        tmp = (int) (x + (i * move));
        if (tmp >= 0 && x + (i * move) < env[y].size()) {
            if (env[y][tmp] == TileType::TILE_EMPTY || env[y][tmp] == TileType::TILE_BONUS)
                env[y][tmp] = TileType::TILE_EXPLOSION;
        }
    }
    for (size_t i = 0; i < range; i++) {
        tmp = (int) (y + (i * move));
        if (tmp >= 0 && y + (i * move) < env.size()) {
            if (env[tmp][x] == TileType::TILE_EMPTY || env[tmp][x] == TileType::TILE_BONUS)
                env[tmp][x] = TileType::TILE_EXPLOSION;
        }
    }
    move = -1;
    for (size_t i = 0; i < range; i++) {
        tmp = (int) (x + (i * move));
        if (tmp >= 0 && x + (i * move) < env[y].size()) {
            if (env[y][tmp] == TileType::TILE_EMPTY || env[y][tmp] == TileType::TILE_BONUS)
                env[y][tmp] = TileType::TILE_EXPLOSION;
        }
    }
    for (size_t i = 0; i < range; i++) {
        tmp = (int) (y + (i * move));
        if (tmp >= 0 && y + (i * move) < env.size()) {
            if (env[tmp][x] == TileType::TILE_EMPTY || env[tmp][x] == TileType::TILE_BONUS)
                env[tmp][x] = TileType::TILE_EXPLOSION;
        }
    }
    return env;
}

IA::Movement IABomberman::getIAMovement()
{
    IA::Movement tmp = IACore::getIAMovement();

    if (this->isSecurePlace(this->_env[this->_prevPos.second][this->_prevPos.first])
        && !this->isSecurePlace(this->_env[this->_pos.second][this->_pos.first])) {
        this->clearQueue(this->_MovementQueue);
        this->_pos = this->_prevPos;
        std::cout << "On a encore eu de la chance" << std::endl;
        return IA::Movement::IA_MOVE_NONE;
    }
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
    std::pair<int, int> tmp = {this->_defaultValue, this->_defaultValue};
    std::vector<std::vector<int>> cost;

    if (this->_enemyPos.size() > 3)
        throw IAExceptions("Invalide enemy list", true);
    cost = this->findEnemy(pos, env);
    for (size_t i = 0; i < this->_enemyPos.size(); i++) {
        if (tmp.first == this->_defaultValue || tmp.second > cost[this->_enemyPos[i].second][this->_enemyPos[i].first]) {
            tmp.first = (int) i;
            tmp.second = cost[this->_enemyPos[i].second][this->_enemyPos[i].first];
        }
    }
    if (!this->_enemyPos.size()) {
        this->clearQueue(list);
        list.push(IA::Movement::IA_MOVE_NONE);
    } else {
        this->loadPath(cost, this->_enemyPos[tmp.first], path);
        this->clearQueue(list);
        if (path.size())
            list.push(path.front());
        else
            list.push(IA::Movement::IA_MOVE_NONE);
        this->clearQueue(path);
    }
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

std::vector<std::vector<int>> IABomberman::findEnemy(const std::pair<size_t, size_t> &pos, const std::vector<std::vector<TileType>> &env) const
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
                    if (x + 1 < cpy[y].size() && cpy[y][x + 1] == this->_defaultValue && env[y][x + 1] != TileType::TILE_HARD)
                        cpy[y][x + 1] = to_find + 1;
                    if (y + 1 < cpy.size() && cpy[y + 1][x] == this->_defaultValue && env[y + 1][x] != TileType::TILE_HARD)
                        cpy[y + 1][x] = to_find + 1;
                    if (x != 0 && cpy[y][x - 1] == this->_defaultValue && env[y][x - 1] != TileType::TILE_HARD)
                        cpy[y][x - 1] = to_find + 1;
                    if (y != 0 && cpy[y - 1][x] == this->_defaultValue && env[y - 1][x] != TileType::TILE_HARD)
                        cpy[y - 1][x] = to_find + 1;
                }
            }
        }
        to_find++;
    }
    return cpy;
}