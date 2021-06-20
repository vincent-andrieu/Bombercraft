/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** MapFactory.hpp
*/

#ifndef MAPFACTORY_HPP
#define MAPFACTORY_HPP

#include "GameEngine.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "EntityPack/EntityPack.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"
#include "Game/ProceduralMap/ProceduralMap.hpp"

namespace Game
{
    class MapFactory {
      public:
        MapFactory() = delete;
        ~MapFactory() = delete;
        static void create(Engine::EntityPack &entityPack,
            const std::string &ressourcePackRoot = "",
            const std::string &name = "",
            unsigned int seed = 0);

        static void updateMapTextures(std::string const &resourcePackRoot, Engine::Entity mapEntity);

      private:
        static GameModule::MapType getProceduralMap(std::pair<size_t, size_t> &sizeDest);
        static GUI::BlockFactory::BlockType blockTypeSinceTile(GameModule::TileType tile);
    };
} // namespace Game

#endif