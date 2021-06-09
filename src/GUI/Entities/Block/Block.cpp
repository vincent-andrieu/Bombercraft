/*
** EPITECH PROJECT, 2021
** Block
** File description:
** Block.cpp
*/

#include "Block.hpp"

using namespace Entities;

Block::Block(Engine::EntityPack &entities, const std::string &name, raylib::MyVector3 pos, BlockType type)
: _type(type), _name(name), _entity(entities.createEntity(name))
{
    raylib::MyVector3 size = Game::CoreData::settings->getMyVector3("DEFAULT_BLOCK_SIZE");
    std::shared_ptr<raylib::Model> model = this->getModel(pos, type);

    Game::CoreData::entityManager->addComponent<Engine::Position>(this->_entity, pos.a, pos.b, pos.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(this->_entity, model);
    if (type != BlockType::BLOCK_FLOOR) {
        Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size,
            []([[maybe_unused]] const Engine::Entity &fromEntity, [[maybe_unused]] const Engine::Entity &toEntity) {
        });
    }
}

Block::~Block()
{

}

std::shared_ptr<raylib::Model> Block::getModel(raylib::MyVector3 pos, BlockType type) const
{
    std::string modelPath = Game::CoreData::settings->getString("BLOCK_MODEL");
    std::string texturePath;
    std::string typeInStr;

    if (type == BlockType::BLOCK_FLOOR)
        typeInStr = "FLOOR";
    else if (type == BlockType::BLOCK_SOFT)
        typeInStr = "SOFT";
    else if (type == BlockType::BLOCK_HARD)
        typeInStr = "HARD";
    else
        throw std::invalid_argument("Not define in enum");
    texturePath = Game::CoreData::settings->getString("BLOCK_" + typeInStr + "_TEXTURE");
    return std::make_shared<raylib::Model>(texturePath, modelPath, pos, raylib::RColor::RWHITE);
}