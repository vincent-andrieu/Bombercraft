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
        TILE_EMPTY,
        TILE_BONUS,
        TILE_SOFT,
        TILE_HARD
    };

    enum class TileDisponibility {
        TILE_AVAILABLE,
        TILE_FORCE_EMPTY,
        TILE_FORCE_HARD,
        TILE_FORCE_SOFT,
        TILE_FORCE_BONUS
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
        virtual std::vector<unsigned char> getHashList() = 0;
        virtual void setHashList(std::vector<unsigned char> hashList) = 0;
        virtual void setModelSettings(std::unordered_map<TileType, unsigned char> linkList) = 0;
    };
}

#endif