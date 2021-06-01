/*
** EPITECH PROJECT, 2021
** YEP
** File description:
** ProceduralMap.hpp
*/

#ifndef PROCEDURALMAP_HPP
#define PROCEDURALMAP_HPP

#include "IProceduralMap.hpp"

using namespace GameModule;

namespace GameModule
{
    class ProceduralMap : public IProceduralMap
    {
        public:
            ProceduralMap(size_t seed = 0);
            ~ProceduralMap();
            void reset();
            MapType getProceduralMap();
            void regenerateProceduralMap();
            void setMapModel(MapDisponibility model);
            std::vector<unsigned char> getHashList();
            void setHashList(std::vector<unsigned char> hashList);
            void setModelSettings(std::unordered_map<TileType, unsigned char> linkList);

        private:
            void generateHash();
            void generateMap();
            bool isCorrectProba() const;
            TileType getTile(TileDisponibility tileType, size_t x, size_t y) const;
            float getPerlinNoise(size_t x, size_t y) const;
            float getNoise(float x, float y) const;
            float applyNoiseFunc(float x, float y, float dec) const;

        private:
            MapType _mapProcedural;
            MapDisponibility _mapModel;
            std::vector<unsigned char> _hash;
            std::unordered_map<TileType, unsigned char> _mapProba;
    };
}

#endif