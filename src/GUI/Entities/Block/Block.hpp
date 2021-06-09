/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Block.hpp
*/

#ifndef BLOCKENTITY_HPP_
#define BLOCKENTITY_HPP_

#include "GameEngine.hpp"
#include "EntityPack/EntityPack.hpp"
#include "Systems/Render2D/Render2DSystem.hpp"
#include "Systems/Render3D/Render3DSystem.hpp"

namespace Entities
{
    class Block
    {
        enum class BlockType
        {
            BLOCK_HARD,
            BLOCK_SOFT,
            BLOCK_BOMB,
            BLOCK_BLAST,
            BLOCK_FLOOR,
            BLOCK_BONUS_BOOMUP,
            BLOCK_BONUS_FIREUP,
            BLOCK_BONUS_SPEEDUP,
            BLOCK_BONUS_WALLPASS,
        };
        public:
            Block(Engine::EntityPack &entities, const std::string &name, raylib::MyVector3 pos, BlockType type);
            ~Block();

        private:
            std::shared_ptr<raylib::Model> getModel(raylib::MyVector3 pos, BlockType type) const;
            // FACTORY
            void internalFactory(BlockType type, raylib::MyVector3 pos, raylib::MyVector3 size);

            // FACTORY_FUNC
            void softFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;
            void hardFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;
            void bombFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;
            void blastFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;
            /*void floorFactory(raylib::MyVector3 pos, raylib::MyVector3 size);*/
            void boomUpBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;
            void fireUpBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;
            void speedUpBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;
            void wallPassBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const;

            // HANDLER
            static void handlerBlastTimer(Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, Engine::Entity entity);
            static void handlerCollision(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerKillEntity(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerBoomUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerFireUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerSpeedUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);
            static void handlerWallPass(const Engine::Entity &fromEntity, const Engine::Entity &toEntity);

        private:
            BlockType _type;
            std::string _name;
            Engine::Entity _entity;
            raylib::MyVector3 _pos;
            std::unordered_map<BlockType, std::function<void(raylib::MyVector3 pos, raylib::MyVector3 size)>> _factory = {
                {BlockType::BLOCK_HARD, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->hardFactory(pos, size);}},
                {BlockType::BLOCK_SOFT, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->softFactory(pos, size);}},
                {BlockType::BLOCK_BOMB, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->bombFactory(pos, size);}},
                {BlockType::BLOCK_BLAST, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->blastFactory(pos, size);}},
                {BlockType::BLOCK_FLOOR, nullptr},
                {BlockType::BLOCK_BONUS_BOOMUP, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->boomUpBonusFactory(pos, size);}},
                {BlockType::BLOCK_BONUS_FIREUP, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->fireUpBonusFactory(pos, size);}},
                {BlockType::BLOCK_BONUS_SPEEDUP, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->speedUpBonusFactory(pos, size);}},
                {BlockType::BLOCK_BONUS_WALLPASS, [this](raylib::MyVector3 pos, raylib::MyVector3 size) {this->wallPassBonusFactory(pos, size);}},
            };
    };
}

#endif /* !EXCEPTIONS_HPP_ */
