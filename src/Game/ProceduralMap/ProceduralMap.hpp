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
    class ProceduralMap : public IProceduralMap {
      public:
        ProceduralMap();
        ~ProceduralMap();
        void reset();
        MapType getProceduralMap();
        void regenerateProceduralMap();
        void setMapModel(MapDisponibility model);
        void setModelSettings(std::unordered_map<TileType, int> linkList);
        std::pair<size_t, size_t> getSize() const;

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
        std::unordered_map<TileType, int> _mapProba;
    };
} // namespace GameModule

#endif