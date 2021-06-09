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
        };
        public:
            Block(Engine::EntityPack &entities, const std::string &name, raylib::MyVector3 pos, BlockType type);
            ~Block();

        private:
            std::shared_ptr<raylib::Model> getModel(raylib::MyVector3 pos, BlockType type) const;
            // FACTORY
            void internalFactory(BlockType type, raylib::MyVector3 pos, raylib::MyVector3 size);

            // FACTORY_FUNC
            void softFactory(raylib::MyVector3 pos, raylib::MyVector3 size);
            void hardFactory(raylib::MyVector3 pos, raylib::MyVector3 size);
            void bombFactory(raylib::MyVector3 pos, raylib::MyVector3 size);
            void blastFactory(raylib::MyVector3 pos, raylib::MyVector3 size);

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
            };
    };
}

#endif /* !EXCEPTIONS_HPP_ */
