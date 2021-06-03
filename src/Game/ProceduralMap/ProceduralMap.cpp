/*
** EPITECH PROJECT, 2021
** YEP
** File description:
** ProceduralMap.cpp
*/

#include <iostream>

#include <ctime>
#include <cmath>
#include <algorithm>
#include "ProceduralMap.hpp"

ProceduralMap::ProceduralMap(size_t seed) : _seed((seed) ? seed : std::time(nullptr))
{
    std::srand(this->_seed);
}

ProceduralMap::~ProceduralMap()
{
    this->reset();
}

void ProceduralMap::reset()
{
    this->_mapProcedural.clear();
    this->_mapModel.clear();
    this->_mapProba.clear();
    this->_seed = 0;
}

void ProceduralMap::regenerateProceduralMap()
{
    this->_mapProcedural.clear();
    this->generateMap();
}

MapType ProceduralMap::getProceduralMap()
{
    this->generateMap();
    return this->_mapProcedural;
}

void ProceduralMap::setMapModel(MapDisponibility model)
{
    this->_mapModel = model;
}

unsigned int ProceduralMap::getSeed()
{
    return this->_seed;
}

void ProceduralMap::setSeed(unsigned int seed)
{
    this->_seed = seed;
    std::srand(this->_seed);
}


void ProceduralMap::setModelSettings(std::unordered_map<TileType, unsigned char> linkList)
{
    this->_mapProba.clear();
    this->_mapProba = linkList;
}

void ProceduralMap::generateMap()
{
    if (!this->_mapModel.size())
        throw std::invalid_argument("Invalide empty model");
    if (!this->isCorrectProba())
        throw std::invalid_argument("Invalide probability");
    this->_mapProcedural.clear();
    this->mapInitEmpty();
    for (auto proba : this->_mapProba) {
        this->randomFill(proba.second, proba.first);
    }
    this->clearMap();
    this->modelApply();
}

void ProceduralMap::randomFill(float prob, TileType type)
{
    size_t totalTile = this->getTotalTile();
    size_t nb = (prob / 100) * totalTile;
    size_t endTile = this->getTotalEmptyTile();
    size_t random = 0;
    GameModule::MapType::iterator map_it_y = this->_mapProcedural.begin();
    std::vector<GameModule::TileType>::iterator map_it_x = map_it_y->begin();

    while (map_it_y != this->_mapProcedural.end()) {
        map_it_x = map_it_y->begin();
        while (map_it_x != map_it_y->end()) {
            if (!nb)
                return;
            if (*map_it_x == TileType::TILE_DEFAULT) {
                random = rand() % 100;
                if (nb >= endTile || random <= prob) {
                    *map_it_x = type;
                    nb--;
                }
                endTile--;
            }
            map_it_x++;
        }
        map_it_y++;
    }
}

void ProceduralMap::modelApply()
{
    auto map_it_y = this->_mapProcedural.begin();
    auto map_it_x = map_it_y->begin();

    for (auto it_y : this->_mapModel) {
        map_it_x = map_it_y->begin();
        for (auto it_x : it_y) {
            switch (it_x)
            {
                case TileDisponibility::TILE_FORCE_EMPTY: *map_it_x = TileType::TILE_EMPTY; break;
                case TileDisponibility::TILE_FORCE_HARD: *map_it_x = TileType::TILE_HARD; break;
                case TileDisponibility::TILE_FORCE_SOFT: *map_it_x = TileType::TILE_SOFT; break;
                case TileDisponibility::TILE_FORCE_BONUS: *map_it_x = TileType::TILE_BONUS; break;
                default:
                    break;
            }
            map_it_x++;
        }
        map_it_y++;
    }
}

bool ProceduralMap::isCorrectProba() const
{
    size_t prob = 0;

    for (auto it : this->_mapProba)
        prob += it.second;
    return (prob == 100) ? true : false;
}

void ProceduralMap::mapInitEmpty()
{
    std::vector<TileType> list;

    for (auto it_y : this->_mapModel) {
        list.clear();
        for (__attribute__ ((unused))auto it : it_y) {
            list.push_back(TileType::TILE_DEFAULT);
        }
        this->_mapProcedural.push_back(list);
    }
}

size_t ProceduralMap::getTotalTile() const
{
    size_t cnt = 0;

    for (auto it_y : this->_mapProcedural) {
        cnt += it_y.size();
    }
    return cnt;
}

size_t ProceduralMap::getTotalEmptyTile() const
{
    size_t cnt = 0;

    for (auto it_y : this->_mapProcedural) {
        for (auto it_x : it_y) {
            if (it_x == TileType::TILE_DEFAULT)
                cnt++;
        }
    }
    return cnt;
}

void ProceduralMap::clearMap()
{
    GameModule::MapType::iterator map_it_y = this->_mapProcedural.begin();
    std::vector<GameModule::TileType>::iterator map_it_x = map_it_y->begin();

    while (map_it_y != this->_mapProcedural.end()) {
        map_it_x = map_it_y->begin();
        while (map_it_x != map_it_y->end()) {
            if (*map_it_x == TileType::TILE_DEFAULT)
                *map_it_x = TileType::TILE_EMPTY;
            map_it_x++;
        }
        map_it_y++;
    }
}