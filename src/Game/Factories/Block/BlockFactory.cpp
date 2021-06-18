/*
** EPITECH PROJECT, 2021
** Block
** File description:
** BlockFactory.cpp
*/

#include "BlockFactory.hpp"
#include "EntityType.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "Components/PlayerInventory/PlayerInventory.hpp"
#include "Systems/Audio/AudioSystem.hpp"

using namespace GUI;

std::unordered_map<BlockFactory::BlockType,
    std::function<void(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)>>
    BlockFactory::_factory = {
        {BlockType::BLOCK_HARD, BlockFactory::hardFactory},
        {BlockType::BLOCK_SOFT, BlockFactory::softFactory},
        {BlockType::BLOCK_BOMB, nullptr},
        {BlockType::BLOCK_BLAST, BlockFactory::blastFactory},
        {BlockType::BLOCK_FLOOR, nullptr},
        {BlockType::BLOCK_BONUS_SOFT, BlockFactory::softBonusFactory},
        {BlockType::BLOCK_BONUS_BOOMUP, BlockFactory::boomUpBonusFactory},
        {BlockType::BLOCK_BONUS_FIREUP, BlockFactory::fireUpBonusFactory},
        {BlockType::BLOCK_BONUS_SPEEDUP, BlockFactory::speedUpBonusFactory},
        {BlockType::BLOCK_BONUS_WALLPASS, BlockFactory::wallPassBonusFactory},
};

Engine::Entity BlockFactory::create(Engine::EntityPack &entityPack,
    const raylib::MyVector3 position,
    BlockType type,
    const std::string &ressourcePackRoot,
    const std::string &name)
{
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    std::shared_ptr<raylib::IModel> model = BlockFactory::getModel(position, type, ressourcePackRoot);
    Engine::Entity entity = (name.size()) ? entityPack.createEntity(name) : entityPack.createAnonymousEntity();
    Engine::Entity entityMap = Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("gameMap");
    const Component::Matrix2D &matrix = Game::CoreData::entityManager->getComponent<Component::Matrix2D>(entityMap);
    raylib::MyVector2 positionOnMap = Component::Matrix2D::getMapIndex(position);

    if (type != BlockFactory::BlockType::BLOCK_FLOOR) {
        matrix.getData()->save({(size_t) positionOnMap.a, (size_t) positionOnMap.b}, entity, type);
    }
    Game::CoreData::entityManager->addComponent<Engine::Position>(entity, position.a, position.b, position.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(entity, model);
    BlockFactory::internalFactory(entity, type, position, size);
    return entity;
}

std::shared_ptr<raylib::IModel> BlockFactory::getModel(
    const raylib::MyVector3 &pos, BlockType type, const std::string &ressourcePackRoot)
{
    std::string modelPath = Game::CoreData::settings->getString("BLOCK_MODEL");
    std::string animPath = Game::CoreData::settings->getString("BLOCK_BLAST_ANIM");
    std::string texturePath;
    std::string typeInStr;

    switch (type) {
        case BlockType::BLOCK_SOFT: typeInStr = "SOFT"; break;
        case BlockType::BLOCK_HARD: typeInStr = "HARD"; break;
        case BlockType::BLOCK_BOMB: typeInStr = "BOMB"; break;
        case BlockType::BLOCK_BLAST: typeInStr = "BLAST"; break;
        case BlockType::BLOCK_FLOOR: typeInStr = "FLOOR"; break;
        case BlockType::BLOCK_BONUS_SOFT: typeInStr = "SOFT"; break;
        case BlockType::BLOCK_BONUS_BOOMUP: typeInStr = "BONUS_BOOMUP"; break;
        case BlockType::BLOCK_BONUS_FIREUP: typeInStr = "BONUS_FIREUP"; break;
        case BlockType::BLOCK_BONUS_SPEEDUP: typeInStr = "BONUS_SPEEDUP"; break;
        case BlockType::BLOCK_BONUS_WALLPASS: typeInStr = "BONUS_WALLPASS"; break;
        default: typeInStr = "DEFAULT"; break;
    }
    texturePath = Game::CoreData::settings->getString("BLOCK_" + typeInStr + "_TEXTURE");
    switch (type) {
        case BlockType::BLOCK_SOFT: texturePath = ressourcePackRoot + texturePath; break;
        case BlockType::BLOCK_FLOOR: texturePath = ressourcePackRoot + texturePath; break;
        case BlockType::BLOCK_BONUS_SOFT: texturePath = ressourcePackRoot + texturePath; break;
        default:; break;
    }
    if (type == BlockType::BLOCK_BLAST) {
        return std::make_shared<raylib::Animation>(texturePath, animPath, pos, raylib::RColor::RWHITE, true);
    }
    return std::make_shared<raylib::Model>(texturePath, modelPath, pos, raylib::RColor::RWHITE);
}

void BlockFactory::internalFactory(
    const Engine::Entity &entity, BlockType type, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    try {
        std::function<void(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)> func =
            BlockFactory::_factory.at(type);

        if (func)
            func(entity, pos, size);
    } catch (const std::out_of_range &e) {
        (void) e;
        return;
    }
}

void BlockFactory::softFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, pos, size, BlockFactory::handlerCollision, Game::EntityType::SOFTBLOCK);
}

void BlockFactory::hardFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, pos, size, BlockFactory::handlerCollision, Game::EntityType::HARDBLOCK);
}

void BlockFactory::blastFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    int blastTime = Game::CoreData::settings->getInt("BLAST_DURATION");
    raylib::MyVector3 blastHitbox = size - (size * raylib::MyVector3(0.5, 0.5, 0.5));
    raylib::MyVector3 newPos = pos + ((size - blastHitbox) / raylib::MyVector3(2, 2, 2));

    if (blastTime < 0)
        blastTime = 0;
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, blastTime, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, BlockFactory::handlerBlastTimer);
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, newPos, blastHitbox, BlockFactory::handlerKillEntity, Game::EntityType::BLAST);
    Game::CoreData::entityManager->addComponent<Engine::Velocity>(entity);
}

void BlockFactory::softBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, pos, size, BlockFactory::handlerCollision, Game::EntityType::SOFTBONUSBLOCK);
}

void BlockFactory::boomUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, pos, size, BlockFactory::handlerBoomUp, Game::EntityType::POWERUP);
}

void BlockFactory::fireUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, pos, size, BlockFactory::handlerFireUp, Game::EntityType::POWERUP);
}

void BlockFactory::speedUpBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, pos, size, BlockFactory::handlerSpeedUp, Game::EntityType::POWERUP);
}

void BlockFactory::wallPassBonusFactory(const Engine::Entity &entity, const raylib::MyVector3 &pos, const raylib::MyVector3 &size)
{
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, pos, size, BlockFactory::handlerWallPass, Game::EntityType::POWERUP);
}

void BlockFactory::handlerBlastTimer(
    UNUSED Engine::EntityManager &entityManager, UNUSED Engine::SceneManager &sceneManager, const Engine::Entity &entity)
{
    auto scene = Game::Core::sceneManager->getCurrentScene();
    raylib::MyVector3 BlastPosition =
        Game::CoreData::entityManager->getComponent<Component::Render3D>(entity).modele->getPosition();
    raylib::MyVector2 indexOnMap = Component::Matrix2D::getMapIndex(BlastPosition);
    Engine::Entity entityMap = Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("gameMap");
    const Component::Matrix2D &matrix = Game::CoreData::entityManager->getComponent<Component::Matrix2D>(entityMap);

    matrix.getData()->save({(size_t) indexOnMap.a, (size_t) indexOnMap.b}, entity, BlockType::BLOCK_AIR);
    // TODO remove blast
    scene->localEntities.removeEntity(entity); // REMOVE BLAST
}

void BlockFactory::handlerCollision(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    // TODO stop moving
    (void) fromEntity;
    (void) toEntity;
}

void BlockFactory::handlerKillEntity(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    auto scene = Game::Core::sceneManager->getCurrentScene();
    auto &hitboxTo = Game::CoreData::entityManager->getComponent<Component::Hitbox>(toEntity);
    auto &render3DTo = Game::CoreData::entityManager->getComponent<Component::Render3D>(toEntity);
    auto &hitboxFrom = Game::CoreData::entityManager->getComponent<Component::Hitbox>(fromEntity);
    BlockFactory::BlockType bonusType;
    std::string texturePath;
    std::string typeInStr;
    const raylib::MyVector3 position = render3DTo.modele->getPosition();

    if (hitboxFrom.entityType == Game::EntityType::BLAST && hitboxTo.entityType == Game::EntityType::SOFTBLOCK) {
        scene->localEntities.removeEntity(toEntity); // REMOVE SOFT BLOCK
        Game::CoreData::systemManager->getSystem<System::AudioSystem>().play("BlockDestroyed");
    }
    if (hitboxFrom.entityType == Game::EntityType::BLAST && hitboxTo.entityType == Game::EntityType::SOFTBONUSBLOCK) {
        bonusType = randomBonus();
        switch (bonusType) {
            case BlockType::BLOCK_BONUS_BOOMUP: typeInStr = "BONUS_BOOMUP"; break;
            case BlockType::BLOCK_BONUS_FIREUP: typeInStr = "BONUS_FIREUP"; break;
            case BlockType::BLOCK_BONUS_SPEEDUP: typeInStr = "BONUS_SPEEDUP"; break;
            case BlockType::BLOCK_BONUS_WALLPASS: typeInStr = "BONUS_WALLPASS"; break;
            default: typeInStr = "DEFAULT"; break;
        }
        texturePath = Game::CoreData::settings->getString("BLOCK_" + typeInStr + "_TEXTURE");
        scene->localEntities.removeEntity(toEntity);   // SOFT BONUS BLOCK
        scene->localEntities.removeEntity(fromEntity); // BLAST
        GUI::BlockFactory::create(scene->localEntities, position, bonusType, texturePath);
    }
    if (hitboxFrom.entityType == Game::EntityType::BLAST && hitboxTo.entityType == Game::EntityType::CHARACTER) {
        std::cout << "Should kill user" << std::endl;
        // scene->localEntities.removeEntity(toEntity); // CHARACTER
    }
    // TODO kill entity if player
}

void BlockFactory::handlerBoomUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    auto &hitboxFrom = Game::CoreData::entityManager->getComponent<Component::Hitbox>(fromEntity);

    if (hitboxFrom.entityType == Game::EntityType::CHARACTER) {
        scene->localEntities.removeEntity(toEntity); // RM BONUS

        auto &inventory = Game::CoreData::entityManager->getComponent<Component::PlayerInventory>(fromEntity);
        const Component::PlayerInventoryInfo &info = inventory.getPlayerInventoryInfo();
        inventory.setBomb(info.bomb + 1);
    }
}

void BlockFactory::handlerFireUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    auto &hitboxFrom = Game::CoreData::entityManager->getComponent<Component::Hitbox>(fromEntity);

    if (hitboxFrom.entityType == Game::EntityType::CHARACTER) {
        scene->localEntities.removeEntity(toEntity); // RM BONUS

        auto &inventory = Game::CoreData::entityManager->getComponent<Component::PlayerInventory>(fromEntity);
        const Component::PlayerInventoryInfo &info = inventory.getPlayerInventoryInfo();
        inventory.setBlastRadius(info.blastRadius + 1);
    }
}

void BlockFactory::handlerSpeedUp(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    auto &hitboxFrom = Game::CoreData::entityManager->getComponent<Component::Hitbox>(fromEntity);

    if (hitboxFrom.entityType == Game::EntityType::CHARACTER) {
        scene->localEntities.removeEntity(toEntity); // RM BONUS

        auto &inventory = Game::CoreData::entityManager->getComponent<Component::PlayerInventory>(fromEntity);
        const Component::PlayerInventoryInfo &info = inventory.getPlayerInventoryInfo();
        if (info.speed < 1) {
            inventory.setSpeed(info.speed + 0.1);
        }
    }
}

void BlockFactory::handlerWallPass(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    auto scene = Game::CoreData::sceneManager->getCurrentScene();
    auto &hitboxFrom = Game::CoreData::entityManager->getComponent<Component::Hitbox>(fromEntity);

    if (hitboxFrom.entityType == Game::EntityType::CHARACTER) {
        scene->localEntities.removeEntity(toEntity); // RM BONUS

        auto &inventory = Game::CoreData::entityManager->getComponent<Component::PlayerInventory>(fromEntity);
        inventory.setWallPass(true);
    }
}

void BlockFactory::blastPropagation(const Engine::Position &pos, Engine::EntityPack &entityPack, const size_t blastRadius)
{
    Engine::Entity entityMap = entityPack.getEntity("gameMap");
    const Component::Matrix2D &matrix = Game::CoreData::entityManager->getComponent<Component::Matrix2D>(entityMap);
    const raylib::MyVector3 &blockSize = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    // TODO SPLIT INTO METHODS
    raylib::MyVector2 vector2 = Component::Matrix2D::getMapIndex(raylib::MyVector3(pos.x, pos.x, pos.z));
    std::pair<Engine::Entity, GUI::BlockFactory::BlockType> blockTmp;

    GUI::BlockFactory::create(entityPack, {pos.x, pos.y, pos.z}, GUI::BlockFactory::BlockType::BLOCK_BLAST);
    for (size_t i = 1; i < blastRadius; i++) {
        blockTmp = matrix.getData({(size_t) vector2.a + i, (size_t) vector2.b});
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_HARD)
            break;
        GUI::BlockFactory::create(entityPack, {pos.x + i * blockSize.a, pos.y, pos.z}, GUI::BlockFactory::BlockType::BLOCK_BLAST);
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_SOFT)
            break;
    }
    for (size_t i = 1; i < blastRadius; i++) {
        blockTmp = matrix.getData({(size_t) vector2.a - i, (size_t) vector2.b});
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_HARD)
            break;
        GUI::BlockFactory::create(entityPack, {pos.x - i * blockSize.a, pos.y, pos.z}, GUI::BlockFactory::BlockType::BLOCK_BLAST);
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_SOFT)
            break;
    }
    for (size_t i = 1; i < blastRadius; i++) {
        blockTmp = matrix.getData({(size_t) vector2.a, (size_t) vector2.b + i});
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_HARD)
            break;
        GUI::BlockFactory::create(entityPack, {pos.x, pos.y, pos.z + i * blockSize.c}, GUI::BlockFactory::BlockType::BLOCK_BLAST);
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_SOFT)
            break;
    }
    for (size_t i = 1; i < blastRadius; i++) {
        blockTmp = matrix.getData({(size_t) vector2.a, (size_t) vector2.b - i});
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_HARD)
            break;
        GUI::BlockFactory::create(entityPack, {pos.x, pos.y, pos.z - i * blockSize.c}, GUI::BlockFactory::BlockType::BLOCK_BLAST);
        if (blockTmp.second == GUI::BlockFactory::BlockType::BLOCK_SOFT)
            break;
    }
}

GUI::BlockFactory::BlockType BlockFactory::randomBonus()
{
    int value = std::rand() % 101;
    int total = 0;
    std::vector<int> prob;
    std::vector<GUI::BlockFactory::BlockType> tab = {
        GUI::BlockFactory::BlockType::BLOCK_BONUS_BOOMUP,
        GUI::BlockFactory::BlockType::BLOCK_BONUS_FIREUP,
        GUI::BlockFactory::BlockType::BLOCK_BONUS_SPEEDUP,
        GUI::BlockFactory::BlockType::BLOCK_BONUS_WALLPASS,
    };

    if (Game::CoreData::settings->isSetInFile("RANDOM_BONUS")) {
        for (size_t i = 0; i < 4; i++)
            prob.push_back(25);
    } else {
        prob = Game::CoreData::settings->getTabInt("RANDOM_BONUS");
    }
    if (prob.size() != 4)
        throw std::invalid_argument("Invalide bonus array of proba");
    for (size_t i = 0; i < 4; i++)
        total += prob[i];
    if (total != 100)
        throw std::invalid_argument("Invalide bonus array of proba");
    total = 0;
    for (size_t i = 0; i < 4; i++) {
        total += prob[i];
        if (value <= total)
            return tab[i];
    }
    return GUI::BlockFactory::BlockType::BLOCK_BONUS_BOOMUP;
}