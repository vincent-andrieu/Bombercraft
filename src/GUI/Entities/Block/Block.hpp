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
            BLOCK_FLOOR,
        };
        public:
            Block(Engine::EntityPack &entities, const std::string &name, raylib::MyVector3 pos, BlockType type);
            ~Block();

        private:
            std::shared_ptr<raylib::Model> getModel(raylib::MyVector3 pos, BlockType type) const;

            private:
                BlockType _type;
                std::string _name;
                Engine::Entity _entity;
    };
}

#endif /* !EXCEPTIONS_HPP_ */
