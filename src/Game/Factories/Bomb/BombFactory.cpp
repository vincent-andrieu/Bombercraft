/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Bomb
*/

#include "Game/Factories/Block/BlockFactory.hpp"
#include "BombFactory.hpp"
#include "Components/Matrix2D/Matrix2D.hpp"
#include "Components/ModelList/ModelList.hpp"
#include "Game/CoreData/CoreData.hpp"
#include "Systems/Audio/AudioSystem.hpp"

using namespace Game;

bool BombFactory::isBombPlacable(float posX, float posY)
{
    std::cerr << "START 19" << std::endl;
    auto map(Game::CoreData::entityManager->getComponent<Component::Matrix2D>(
        Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("gameMap")));
    std::cerr << "END 19" << std::endl;
    auto my_data(map.getData(std::make_pair(static_cast<size_t>(posX), static_cast<size_t>(posY))));

    if (my_data.second == GUI::BlockFactory::BlockType::BLOCK_AIR) {
        return true;
    }
    return false;
}

raylib::MyVector2 BombFactory::getNextPos(const raylib::MyVector2 &position, const float rotation)
{
    auto my_position(position);

    if (rotation == 0)
        my_position.b++;
    if (rotation == 90)
        my_position.a--;
    if (rotation == 180)
        my_position.b--;
    if (rotation == 270)
        my_position.a++;
    return my_position;
}

bool BombFactory::placeBomb(Engine::Entity character)
{
    std::cerr << "START 20" << std::endl;
    Component::ModelList &render = Game::CoreData::entityManager->getComponent<Component::ModelList>(character);
    std::cerr << "END 20" << std::endl;
    std::cerr << "START 21" << std::endl;
    const Component::Hitbox &hitbox = Game::CoreData::entityManager->getComponent<Component::Hitbox>(character);
    std::cerr << "END 21" << std::endl;
    auto characterOrientation(render.getRotation().b);
    auto characterPosition(hitbox.objectBox->getBoxOrigin() + hitbox.objectBox->getBoxSize() / 2);
    auto bombIndexOnMap(getNextPos(Component::Matrix2D::getMapIndex(characterPosition), characterOrientation));
    const auto bombPosition(Component::Matrix2D::getPositionAbs((size_t) bombIndexOnMap.a, (size_t) bombIndexOnMap.b));
    std::cerr << "START 22" << std::endl;
    const Engine::EntityBox &inventoryEntityBox = Game::CoreData::entityManager->getComponent<Engine::EntityBox>(character);
    std::cerr << "END 22" << std::endl;
    std::cerr << "START 23" << std::endl;
    Component::PlayerInventory &playerInventory =
        Game::CoreData::entityManager->getComponent<Component::PlayerInventory>(inventoryEntityBox.entity);
    std::cerr << "END 23" << std::endl;
    const Component::PlayerInventoryInfo &inventoryInfo = playerInventory.getPlayerInventoryInfo();

    if (inventoryInfo.bomb && isBombPlacable(bombIndexOnMap.a, bombIndexOnMap.b)) {
        playerInventory.setBomb(inventoryInfo.bomb - 1);
        BombFactory::create(Game::Core::sceneManager->getCurrentScene()->localEntities, bombPosition, character);
        render.select("setBomb");
        return true;
    }
    return false;
}

Engine::Entity BombFactory::create(
    Engine::EntityPack &entityPack, const raylib::MyVector3 position, Engine::Entity entityParent, const std::string &name)
{
    Engine::Entity entityMap = Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("gameMap");
    std::cerr << "START 24" << std::endl;
    const Component::Matrix2D &matrix = Game::CoreData::entityManager->getComponent<Component::Matrix2D>(entityMap);
    std::cerr << "END 24" << std::endl;
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    std::shared_ptr<raylib::Animation> animation = BombFactory::getAnimation(position);
    raylib::MyVector2 positionOnMap = Component::Matrix2D::getMapIndex(position);
    Engine::Entity entity = (name.size()) ? entityPack.createEntity(name) : entityPack.createAnonymousEntity();
    int bombCountdown = Game::CoreData::settings->getInt("BOMB_COUNTDOWN");

    matrix.getData()->save(
        {(size_t) positionOnMap.a, (size_t) positionOnMap.b}, entity, GUI::BlockFactory::BlockType::BLOCK_BOMB);
    Game::CoreData::entityManager->addComponent<Engine::Position>(entity, position.a, position.b, position.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(entity, animation);
    if (bombCountdown < 0)
        bombCountdown = 0;
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, position, size, BombFactory::handlerBombCollision, Game::EntityType::BOMB);
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, bombCountdown, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, BombFactory::handlerBombTimer);
    Game::CoreData::entityManager->addComponent<Engine::EntityBox>(entity, entityParent);
    Game::CoreData::systemManager->getSystem<System::AudioSystem>().play("ActiveBomb");
    return entity;
}

std::shared_ptr<raylib::Animation> BombFactory::getAnimation(const raylib::MyVector3 &pos)
{
    std::string animationPath = Game::CoreData::settings->getString("BOMB_ANIM");
    std::string typeInStr = "BOMB";
    std::string texturePath = Game::CoreData::settings->getString("BOMB_ANIM_TEXTURE");

    return std::make_shared<raylib::Animation>(texturePath, animationPath, pos, raylib::RColor::RWHITE);
}

void BombFactory::handlerBombCollision(const Engine::Entity fromEntity, const Engine::Entity toEntity)
{
    std::cerr << "START 25" << std::endl;
    auto &hitboxFrom = Game::CoreData::entityManager->getComponent<Component::Hitbox>(fromEntity);
    std::cerr << "END 25" << std::endl;

    if (hitboxFrom.entityType == Game::EntityType::BLAST) {
        if (Game::CoreData::entityManager->hasComponent<Engine::Timer>(toEntity)) {
            std::cerr << "START 26" << std::endl;
            Game::CoreData::entityManager->getComponent<Engine::Timer>(toEntity).script.trigger(toEntity);
            std::cerr << "END 26" << std::endl;
        }
    }
}

void BombFactory::handlerBombTimer(
    Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity)
{
    auto scene = Game::Core::sceneManager->getCurrentScene();
    std::cerr << "START 27" << std::endl;
    Engine::Position &pos = entityManager.getComponent<Engine::Position>(entity);
    std::cerr << "END 27" << std::endl;
    std::cerr << "START 28" << std::endl;
    Engine::Entity player = entityManager.getComponent<Engine::EntityBox>(entity).entity;
    std::cerr << "END 28" << std::endl;
    std::cerr << "START 29" << std::endl;
    Engine::EntityBox &playerInventoryEntity = entityManager.getComponent<Engine::EntityBox>(player);
    std::cerr << "END 29" << std::endl;
    std::cerr << "START 30" << std::endl;
    Component::PlayerInventory &playerInventory =
        entityManager.getComponent<Component::PlayerInventory>(playerInventoryEntity.entity);
    std::cerr << "END 30" << std::endl;
    const Component::PlayerInventoryInfo &inventoryInfo = playerInventory.getPlayerInventoryInfo();

    Game::CoreData::systemManager->getSystem<System::AudioSystem>().play("Explosion");
    playerInventory.setBomb(inventoryInfo.bomb + 1);
    GUI::BlockFactory::blastPropagation(pos, sceneManager.getCurrentScene()->localEntities, inventoryInfo.blastRadius);
    scene->localEntities.removeEntity(entity); // BOMB
}