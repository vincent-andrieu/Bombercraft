/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 14/06/2021 CharacterFactory.hpp.h
*/

#ifndef CHARACTERFACTORY_HPP
#define CHARACTERFACTORY_HPP

#include "GameEngine.hpp"
#include "Components/PlayerConfig/PlayerConfig.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "raylib.hpp"
#include "../../../Components/PlayerConfig/PlayerConfig.hpp"

namespace Game
{
    /**
     * PlayerConfig & (skinPath, keyBiding, position)
     *
     */

    class CharacterFactory {
      public:
        virtual ~CharacterFactory() = 0;

        static Engine::Entity create(
            Engine::EntityPack &pack, Component::PlayerConfig &config, Component::Matrix2D &map, bool isAI);

      private:
        /**
         * ALPHA    : TOP LEFT
         * BRAVO    : TOP RIGHT
         * CHARLIE  : BOTTOM LEFT
         * DELTA    : BOTTOM RIGHT
         */
        static raylib::MyVector3 getPlayerPosition(Component::PlayerID id, Component::Matrix2D &map);
        static raylib::MyVector2 getInventoryPosition(Component::PlayerID id);

        static Engine::Entity createPlayer(Engine::Entity entity, Component::PlayerConfig &config);
        static Engine::Entity createAI(Engine::Entity entity);
        static void handlerAITimer(Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity);
    };
} // namespace Game

#endif // CHARACTERFACTORY_HPP
