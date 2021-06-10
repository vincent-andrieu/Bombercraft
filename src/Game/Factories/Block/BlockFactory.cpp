/*
** EPITECH PROJECT, 2021
** Block
** File description:
** BlockFactory.cpp
*/

#include "BlockFactory.hpp"

using namespace GUI;

std::unordered_map<BlockFactory::BlockType, std::function<void(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)>> BlockFactory::_factory =
{
    {BlockType::BLOCK_HARD, BlockFactory::hardFactory},
    {BlockType::BLOCK_SOFT, BlockFactory::softFactory},
    {BlockType::BLOCK_BOMB, BlockFactory::bombFactory},
    {BlockType::BLOCK_BLAST, BlockFactory::blastFactory},
    {BlockType::BLOCK_FLOOR, nullptr},
    {BlockType::BLOCK_BONUS_BOOMUP, BlockFactory::boomUpBonusFactory},
    {BlockType::BLOCK_BONUS_FIREUP, BlockFactory::fireUpBonusFactory},
    {BlockType::BLOCK_BONUS_SPEEDUP, BlockFactory::speedUpBonusFactory},
    {BlockType::BLOCK_BONUS_WALLPASS, BlockFactory::wallPassBonusFactory},
};

void BlockFactory::create(Engine::EntityPack &entityPack, const raylib::MyVector3 position, BlockType type, const std::string &name)
{
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("DEFAULT_BLOCK_SIZE");
    std::shared_ptr<raylib::Model> model = BlockFactory::getModel(position, type);
    const Engine::Entity &entity = entityPack.createEntity(name);

    Game::CoreData::entityManager->addComponent<Engine::Position>(entity, position.a, position.b, position.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(entity, model);
    BlockFactory::internalFactory(entity, type, position, size);
}

std::shared_ptr<raylib::Model> BlockFactory::getModel(const raylib::MyVector3 &pos, BlockType type)
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

void BlockFactory::internalFactory(const Engine::Entity &entity, BlockType type, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    try {
        std::function<void (const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)> func = BlockFactory::_factory.at(type);

        if (func)
            func(entity, pos, size);
    } catch (const std::out_of_range &e) {
        (void) e;
        return;
    }
}

void BlockFactory::softFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerCollision);
}

void BlockFactory::hardFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerCollision);
}

void BlockFactory::bombFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerCollision);
}

void BlockFactory::blastFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    int blastTime = Game::CoreData::settings->getInt("BLAST_DURATION");

    if (blastTime < 0)
        blastTime = 0;
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerKillEntity);
    Game::CoreData::entityManager->addComponent<Engine::Timer>(entity, blastTime, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, BlockFactory::handlerBlastTimer);
}

void BlockFactory::boomUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerBoomUp);
}

void BlockFactory::fireUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerFireUp);
}

void BlockFactory::speedUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerSpeedUp);
}

void BlockFactory::wallPassBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(entity, pos, size, BlockFactory::handlerWallPass);
}


void BlockFactory::handlerBlastTimer(Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity)
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
