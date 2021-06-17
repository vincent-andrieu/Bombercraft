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

using namespace GUI;

bool BombFactory::isBombPlacable(float posX, float posY)
{
    auto map(Game::CoreData::entityManager->getComponent<Component::Matrix2D>(
        Game::CoreData::sceneManager->getCurrentScene()->localEntities.getEntity("gameMap")));
    auto my_data(map.getData(std::make_pair(posX, posY)));

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
    Component::ModelList &render = Game::CoreData::entityManager->getComponent<Component::ModelList>(character);
    const Component::Hitbox &hitbox = Game::CoreData::entityManager->getComponent<Component::Hitbox>(character);
    auto characterOrientation(render.getRotation().b);
    auto characterPosition(hitbox.objectBox->getBoxOrigin() + hitbox.objectBox->getBoxSize() / 2);
    auto bombIndexOnMap(getNextPos(Component::Matrix2D::getMapIndex(characterPosition), characterOrientation));
    const auto bombPosition(Component::Matrix2D::getPositionAbs((size_t) bombIndexOnMap.a, (size_t) bombIndexOnMap.b));

    if (isBombPlacable(bombIndexOnMap.a, bombIndexOnMap.b)) {
        GUI::BombFactory::create(Game::Core::sceneManager->getCurrentScene()->localEntities, bombPosition, character);
        render.select("setBomb");
        return true;
    }
    return false;
}

bool BombFactory::placeBomb(
    Engine::Entity character, const raylib::MyVector3 &characterPosition, const float characterOrientation)
{
    auto bombIndexOnMap(getNextPos(Component::Matrix2D::getMapIndex(characterPosition), characterOrientation));
    const auto bombPosition(Component::Matrix2D::getPositionAbs((size_t) bombIndexOnMap.a, (size_t) bombIndexOnMap.b));

    if (isBombPlacable(bombIndexOnMap.a, bombIndexOnMap.b)) {
        GUI::BombFactory::create(Game::Core::sceneManager->getCurrentScene()->localEntities, bombPosition, character);
        return true;
    }
    return false;
}

Engine::Entity BombFactory::create(
    Engine::EntityPack &entityPack, const raylib::MyVector3 position, Engine::Entity entityParent, const std::string &name)
{
    const raylib::MyVector3 &size = Game::CoreData::settings->getMyVector3("STANDARD_BLOCK_SIZE");
    std::shared_ptr<raylib::Model> model = BombFactory::getModel(position);
    Engine::Entity entity = (name.size()) ? entityPack.createEntity(name) : entityPack.createAnonymousEntity();
    int bombCountdown = Game::CoreData::settings->getInt("BOMB_COUNTDOWN");

    Game::CoreData::entityManager->addComponent<Engine::Position>(entity, position.a, position.b, position.c);
    Game::CoreData::entityManager->addComponent<Component::Render3D>(entity, model);
    if (bombCountdown < 0)
        bombCountdown = 0;
    Game::CoreData::entityManager->addComponent<Component::Hitbox>(
        entity, position, size, BombFactory::handlerBombCollision, Game::EntityType::BOMB);
    Game::CoreData::entityManager->addComponent<Engine::Timer>(
        entity, bombCountdown, *Game::CoreData::entityManager, *Game::CoreData::sceneManager, BombFactory::handlerBombTimer);
    Game::CoreData::entityManager->addComponent<Engine::EntityBox>(entity, entityParent);
    return entity;
}

std::shared_ptr<raylib::Model> BombFactory::getModel(const raylib::MyVector3 &pos)
{
    std::string modelPath = Game::CoreData::settings->getString("BLOCK_MODEL");
    std::string typeInStr = "BOMB";
    std::string texturePath = Game::CoreData::settings->getString("BLOCK_" + typeInStr + "_TEXTURE");

    return std::make_shared<raylib::Model>(texturePath, modelPath, pos, raylib::RColor::RWHITE);
}

void BombFactory::handlerBombCollision(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    // TODO stop moving
    (void) fromEntity;
    (void) toEntity;
}

void BombFactory::handlerBombTimer(
    Engine::EntityManager &entityManager, Engine::SceneManager &sceneManager, const Engine::Entity &entity)
{
    auto scene = Game::Core::sceneManager->getCurrentScene();
    Engine::Position &pos = entityManager.getComponent<Engine::Position>(entity);
    Engine::EntityBox &player = entityManager.getComponent<Engine::EntityBox>(entity);
    Component::PlayerInventory &playerInventory = entityManager.getComponent<Component::PlayerInventory>(player.entity);
    const Component::PlayerInventoryInfo &inventoryInfo = playerInventory.getPlayerInventoryInfo();

    BlockFactory::blastPropagation(pos, sceneManager.getCurrentScene()->localEntities, inventoryInfo.blastRadius);
    scene->localEntities.removeEntity(entity);
}