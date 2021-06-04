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
            ProceduralMap(unsigned int seed = 0);
            ~ProceduralMap();
            void reset();
            MapType getProceduralMap();
            void regenerateProceduralMap();
            void setMapModel(MapDisponibility model);
            unsigned int getSeed();
            void setSeed(unsigned int seed);
            void setModelSettings(std::unordered_map<TileType, unsigned char> linkList);

        private:
            void modelApply();
            void generateMap();
            void mapInitEmpty();
            bool isCorrectProba() const;
            void randomFill(float prob, TileType type);
            size_t getTotalTile() const;
            size_t getTotalEmptyTile() const;
            void clearMap();

        private:
            MapType _mapProcedural;
            MapDisponibility _mapModel;
            unsigned int _seed;
            std::unordered_map<TileType, unsigned char> _mapProba;
    };
}

#endif