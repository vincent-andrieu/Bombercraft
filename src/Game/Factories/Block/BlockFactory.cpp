/*
** EPITECH PROJECT, 2021
** Block
** File description:
** BlockFactory.cpp
*/

#include "BlockFactory.hpp"

using namespace GUI;

BlockFactory::BlockFactory(Engine::EntityPack &entities, const std::string &name, raylib::MyVector3 pos, BlockType type)
: _type(type), _name(name), _entity(entities.createEntity(name)), _pos(pos)
{
    raylib::MyVector3 size = Game::CoreData::settings->getMyVector3("DEFAULT_BLOCK_SIZE");
    std::shared_ptr<raylib::Model> model = this->getModel(pos, type);

    Game::CoreData::entityManager->addComponent<Engine::Position>(this->_entity, pos.a, pos.b, pos.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(this->_entity, model);
    this->internalFactory(type, pos, size);
}

BlockFactory::~BlockFactory()
{
}

std::shared_ptr<raylib::Model> BlockFactory::getModel(raylib::MyVector3 pos, BlockType type) const
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
        case BlockType::BLOCK_BONUS_BOOMUP: typeInStr = "BONUS_BOOMUP"; break;
        case BlockType::BLOCK_BONUS_FIREUP: typeInStr = "BONUS_FIREUP"; break;
        case BlockType::BLOCK_BONUS_SPEEDUP: typeInStr = "BONUS_SPEEDUP"; break;
        case BlockType::BLOCK_BONUS_WALLPASS: typeInStr = "BONUS_WALLPASS"; break;
        default: typeInStr = "DEFAULT"; break;
    }
    texturePath = Game::CoreData::settings->getString("BLOCK_" + typeInStr + "_TEXTURE");
    return std::make_shared<raylib::Model>(texturePath, modelPath, pos, raylib::RColor::RWHITE);
}

void BlockFactory::internalFactory(BlockType type, raylib::MyVector3 pos, raylib::MyVector3 size)
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

void BlockFactory::softFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerCollision);
}

void BlockFactory::hardFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerCollision);
}

void BlockFactory::bombFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerCollision);
}

void BlockFactory::blastFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    int blastTime = Game::CoreData::settings->getInt("BLAST_DURATION");

    if (blastTime < 0)
        blastTime = 0;
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerKillEntity);
    Game::CoreData::entityManager->addComponent<Engine::Timer>(this->_entity, blastTime, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, BlockFactory::handlerBlastTimer);
}

void BlockFactory::boomUpBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerBoomUp);
}

void BlockFactory::fireUpBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerFireUp);
}

void BlockFactory::speedUpBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerSpeedUp);
}

void BlockFactory::wallPassBonusFactory(raylib::MyVector3 pos, raylib::MyVector3 size) const
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(this->_entity, pos, size, BlockFactory::handlerWallPass);
}


void BlockFactory::handlerBlastTimer(Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, Engine::Entity entity)
{
    // TODO remove blast
    (void) sceneManager;
    entityManager.removeEntity(entity);
}

void BlockFactory::handlerCollision(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    // TODO stop moving
    (void) fromEntity;
    (void) toEntity;
}

void BlockFactory::handlerKillEntity(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    (void) fromEntity;
    // TODO kill entity if player
    Game::CoreData::entityManager->removeEntity(toEntity);
}

void BlockFactory::handlerBoomUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    Game::CoreData::entityManager->removeEntity(fromEntity);
    (void) toEntity; // TODO give bonus to this entity if player
}

void BlockFactory::handlerFireUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    Game::CoreData::entityManager->removeEntity(fromEntity);
    (void) toEntity; // TODO give bonus to this entity if player
}

void BlockFactory::handlerSpeedUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    Game::CoreData::entityManager->removeEntity(fromEntity);
    (void) toEntity; // TODO give bonus to this entity if player
}

void BlockFactory::handlerWallPass(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    Game::CoreData::entityManager->removeEntity(fromEntity);
    (void) toEntity; // TODO give bonus to this entity if player
}
