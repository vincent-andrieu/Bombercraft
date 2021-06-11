/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** MapFactory.hpp
*/

#ifndef MAPFACTORY_HPP
#define MAPFACTORY_HPP

#include "GameEngine.hpp"
#include "Component/Matrix2D.hpp"
#include "EntityPack/EntityPack.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Game/ProceduralMap/ProceduralMap.hpp"
#include "../Block/BlockFactory.hpp"

namespace GUI
{
    class MapFactory
    {
        public:
            MapFactory() = delete;
            ~MapFactory() = delete;
            static void create(Engine::EntityPack &entityPack, const std::string &name = "", unsigned int seed = 0);
        
        private:
            static GameModule::MapType getProceduralMap(unsigned int seed, std::pair<size_t, size_t> &sizeDest);
            static GUI::BlockFactory::BlockType blockTypeSinceTile(GameModule::TileType tile);
            static GUI::BlockFactory::BlockType randomBonus();
    };
}

#endif