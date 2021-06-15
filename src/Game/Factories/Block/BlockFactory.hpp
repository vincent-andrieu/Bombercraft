/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** BlockFactory.hpp
*/

#ifndef BLOCKFACTORY_HPP
#define BLOCKFACTORY_HPP

#include "GameEngine.hpp"
#include "EntityPack/EntityPack.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"

namespace GUI
{
    class BlockFactory
    {
        public:
            enum class BlockType
            {
                BLOCK_HARD,
                BLOCK_SOFT,
                BLOCK_BOMB,
                BLOCK_BLAST,
                BLOCK_FLOOR,
                BLOCK_BONUS_SOFT,
                BLOCK_BONUS_BOOMUP,
                BLOCK_BONUS_FIREUP,
                BLOCK_BONUS_SPEEDUP,
                BLOCK_BONUS_WALLPASS,
            };

        public:
            BlockFactory() = delete;
            ~BlockFactory() = delete;
            static Engine::Entity create(Engine::EntityPack &entityPack, const raylib::MyVector3 position, BlockType type, const std::string &ressourcePackRoot = "", const std::string &name = "");

        private:
            static std::shared_ptr<raylib::Model> getModel(const raylib::MyVector3 &pos, BlockType type);
            // FACTORY
            static void internalFactory(const Engine::Entity &entity, BlockType type, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);

            // FACTORY_FUNC
            static void softFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            static void hardFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            static void bombFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            static void blastFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            /*void floorFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);*/
            static void softBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            static void boomUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            static void fireUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            static void speedUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);
            static void wallPassBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size);

            // HANDLER
            static void handlerBombTimer(Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity);
            static void handlerBlastTimer(Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity);
            static void handlerCollision(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerKillEntity(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerBoomUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerFireUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerSpeedUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerWallPass(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);

            // TOOLS
            static void blastPropagation(const Engine::Position &pos, Engine::EntityPack &entityPack);

        private:
            static std::unordered_map<BlockFactory::BlockType, std::function<void(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)>> _factory;
    };
}

#endif
