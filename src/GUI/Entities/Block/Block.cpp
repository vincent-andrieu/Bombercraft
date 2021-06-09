/*
** EPITECH PROJECT, 2021
** Block
** File description:
** Block.cpp
*/

#include "Block.hpp"

using namespace Entities;

Block::Block(Engine::EntityPack &entities, const std::string &name, raylib::MyVector3 pos, BlockType type)
: _type(type), _name(name), _entity(entities.createEntity(name)), _pos(pos)
{
    raylib::MyVector3 size = Game::CoreData::settings->getMyVector3("DEFAULT_BLOCK_SIZE");
    std::shared_ptr<raylib::Model> model = this->getModel(pos, type);

    Game::CoreData::entityManager->addComponent<Engine::Position>(this->_entity, pos.a, pos.b, pos.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(this->_entity, model);
    this->internalFactory(type, pos, size);
}

Block::~Block()
{
}

std::shared_ptr<raylib::Model> Block::getModel(raylib::MyVector3 pos, BlockType type) const
{
    std::string modelPath = Game::CoreData::settings->getString("BLOCK_MODEL");
    std::string texturePath;
    std::string typeInStr;

    switch (type)
    {
        case BlockType::BLOCK_SOFT: typeInStr = "SOFT"; break;
        case BlockType::BLOCK_HARD: typeInStr = "HARD"; break;
        case BlockType::BLOCK_BOMB: typeInStr = "BOMB"; break;
        case BlockType::BLOCK_BLAST: typeInStr = "BLAST"; break;
        case BlockType::BLOCK_FLOOR: typeInStr = "FLOOR"; break;
        default: typeInStr = "DEFAULT"; break;
    }
    texturePath = Game::CoreData::settings->getString("BLOCK_" + typeInStr + "_TEXTURE");
    return std::make_shared<raylib::Model>(texturePath, modelPath, pos, raylib::RColor::RWHITE);
}

void Block::internalFactory(BlockType type, raylib::MyVector3 pos, raylib::MyVector3 size)
{
    try {
        std::function<void (raylib::MyVector3 pos, raylib::MyVector3 size)> func = this->_factory.at(type);

        if (func)
            func(pos, size);
    } catch (const std::out_of_range &e) {
        (void) e;
        return;
    }
}

void Block::softFactory(raylib::MyVector3 pos, raylib::MyVector3 size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size,
        []([[maybe_unused]] const Engine::Entity &fromEntity, [[maybe_unused]] const Engine::Entity &toEntity) {
            // TODO ADD CALLBACK UNDOMOVE
    });
}

void Block::hardFactory(raylib::MyVector3 pos, raylib::MyVector3 size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size,
        []([[maybe_unused]] const Engine::Entity &fromEntity, [[maybe_unused]] const Engine::Entity &toEntity) {
            // TODO ADD CALLBACK UNDOMOVE
    });
}

void Block::bombFactory(raylib::MyVector3 pos, raylib::MyVector3 size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size,
        []([[maybe_unused]] const Engine::Entity &fromEntity, [[maybe_unused]] const Engine::Entity &toEntity) {
            // TODO ADD CALLBACK UNDOMOVE
    });
}

void Block::blastFactory(raylib::MyVector3 pos, raylib::MyVector3 size)
{
    int blastTime = Game::CoreData::settings->getInt("BLAST_DURATION");

    if (blastTime < 0)
        blastTime = 0;
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size,
        []([[maybe_unused]] const Engine::Entity &fromEntity, [[maybe_unused]] const Engine::Entity &toEntity) {
            // TODO ADD CALLBACK KILLENTITY
    });
    Game::CoreData::entityManager->addComponent<Engine::Timer>(this->_entity, blastTime, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, Block::handlerBlastTimer);
}

void Block::handlerBlastTimer(Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, Engine::Entity entity)
{
    (void) entityManager;
    (void) sceneManager;
    (void) entity;
}