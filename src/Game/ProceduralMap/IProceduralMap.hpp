/*
** EPITECH PROJECT, 2021
** YEP
** File description:
** IProceduralMap.hpp
*/

#ifndef IPROCEDURALMAP_HPP
#define IPROCEDURALMAP_HPP

#include <vector>
#include <unordered_map>

namespace GameModule
{
    enum class TileType {
        TILE_EXPLOSION,
        TILE_DEFAULT,
        TILE_DANGER,
        TILE_EMPTY,
        TILE_BONUS,
        TILE_BOMB,
        TILE_SOFT,
        TILE_HARD,
    };

    enum class TileDisponibility {
        TILE_AVAILABLE = 0,
        TILE_FORCE_EMPTY = 1,
        TILE_FORCE_HARD = 2,
        TILE_FORCE_SOFT = 3,
        TILE_FORCE_BONUS = 4
    };

    typedef std::vector<std::vector<TileType>> MapType;
    typedef std::vector<std::vector<TileDisponibility>> MapDisponibility;

    class IProceduralMap {
      public:
        virtual ~IProceduralMap() {};
        virtual void reset() = 0;
        virtual MapType getProceduralMap() = 0;
        virtual void regenerateProceduralMap() = 0;
        virtual void setMapModel(MapDisponibility model) = 0;
        virtual unsigned int getSeed() = 0;
        virtual void setSeed(unsigned int seed) = 0;
        virtual void setModelSettings(std::unordered_map<TileType, int> linkList) = 0;
        virtual std::pair<size_t, size_t> getSize() const = 0;
    };
}

#endif