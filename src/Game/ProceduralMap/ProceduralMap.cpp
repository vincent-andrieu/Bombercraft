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

ProceduralMap::ProceduralMap(size_t seed)
{
    std::srand((seed) ? seed : std::time(nullptr));
    this->generateHash();
}

ProceduralMap::~ProceduralMap()
{
    this->reset();
}

void ProceduralMap::reset()
{
    this->_hash.clear();
    this->_mapProcedural.clear();
    this->_mapModel.clear();
    this->_mapProba.clear();
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

std::vector<unsigned char> ProceduralMap::getHashList()
{
    return this->_hash;
}

void ProceduralMap::setHashList(std::vector<unsigned char> hashList)
{
    if (hashList.size() != 256)
        throw std::invalid_argument("Invalide hash list size");
    this->_hash = hashList;
}

void ProceduralMap::setModelSettings(std::unordered_map<TileType, unsigned char> linkList)
{
    this->_mapProba.clear();
    this->_mapProba = linkList;
}

void ProceduralMap::generateHash()
{
    unsigned char tmp = 0;
    std::vector<unsigned char>::const_iterator it;

    this->_hash.clear();
    for (size_t i = 0; i < 256; i++) {
        do {
            tmp = std::rand() % 256;
            it = std::find(this->_hash.begin(), this->_hash.end(), tmp);
        } while (it != this->_hash.end());
        this->_hash.push_back(tmp);
    }
}

void ProceduralMap::generateMap()
{
    size_t x = 0;
    size_t y = 0;
    std::vector<TileType> list;

    if (this->_hash.size() != 256)
        throw std::invalid_argument("Invalide hash size");
    if (!this->_mapModel.size())
        throw std::invalid_argument("Invalide empty model");
    if (!this->isCorrectProba())
        throw std::invalid_argument("Invalide probability");

    this->_mapProcedural.clear();
    for (auto it_y : this->_mapModel) {
        x = 0;
        list.clear();
        for (auto it_x : it_y) {
            list.push_back(this->getTile(it_x, x++, y));
        }
        this->_mapProcedural.push_back(list);
        y++;
    }
    
}

bool ProceduralMap::isCorrectProba() const
{
    size_t prob = 0;

    for (auto it : this->_mapProba)
        prob += it.second;
    return (prob == 100) ? true : false;
}

TileType ProceduralMap::getTile(TileDisponibility tileType, size_t x, size_t y) const
{
    float tmp;
    float perlin = 0;
    size_t prob_pos = 0;

    switch (tileType)
    {
        case TileDisponibility::TILE_FORCE_EMPTY: return TileType::TILE_EMPTY; break;
        case TileDisponibility::TILE_FORCE_HARD: return TileType::TILE_HARD; break;
        case TileDisponibility::TILE_FORCE_SOFT: return TileType::TILE_SOFT; break;
        case TileDisponibility::TILE_FORCE_BONUS: return TileType::TILE_BONUS; break;
    }
    perlin = getPerlinNoise(x, y);
    for (auto it : this->_mapProba) {
        prob_pos += it.second;
        tmp = (float) prob_pos / 100;
        if (tmp > perlin)
            return it.first;
    }
    return TileType::TILE_EMPTY;
}

float ProceduralMap::getPerlinNoise(size_t x, size_t y) const
{
    float etaloned_x = (float) x / 20;
    float etaloned_y = (float) y / 20;
    float noise_val = 0;
    float amplitude = 1;

    for (size_t i = 0; i < 4; i++) {
        noise_val += this->getNoise(etaloned_x, etaloned_y) * amplitude;
        amplitude /= 2;
        etaloned_x *= 2;
        etaloned_y *= 2;
    }
    std::cout << "noise val: " << noise_val << std::endl;
    return noise_val;
}

float ProceduralMap::getNoise(float x, float y) const
{
    int int_x = std::floor(x);
    int int_y = std::floor(y);
    float dec_x = (float) x - int_x;
    float dec_y = (float) y - int_y;
    int vector_one = this->_hash[(int_x + this->_hash[int_y % 256]) % 256];
    int vector_two = this->_hash[((int_x + 1) + this->_hash[(int_y + 1) % 256]) % 256];
    int vector_three = this->_hash[((int_x + 1) + this->_hash[int_y % 256]) % 256];
    int vector_four = this->_hash[(int_x + this->_hash[(int_y + 1) % 256]) % 256];
    float one = this->applyNoiseFunc(vector_one, vector_three, dec_x);
    float two = this->applyNoiseFunc(vector_two, vector_four, dec_x);

    return this->applyNoiseFunc(one, two, dec_y);
}

float ProceduralMap::applyNoiseFunc(float x, float y, float dec) const
{
    float tmp = (float) dec * dec * 3 - 2 * dec * dec * dec;

    tmp = tmp * (y - x) + x;
    return tmp;
}