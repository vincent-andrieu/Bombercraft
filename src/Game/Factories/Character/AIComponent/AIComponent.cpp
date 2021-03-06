/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** AIComponent.cpp
*/

#include "AIComponent.hpp"

using namespace Component;

AIComponent::AIComponent() : _AI(std::make_shared<GameModule::IABomberman>()), _smoothMode(false), _isSet(false)
{
}

std::pair<double, double> AIComponent::getVelocity()
{
    IA::Movement move;

    move = this->_AI->getIAMovement();
    switch (move)
    {
        case IA::Movement::IA_MOVE_UP: return {0, -2};break;
        case IA::Movement::IA_MOVE_DOWN: return {0, 2};break;
        case IA::Movement::IA_MOVE_LEFT: return {-2, 0};break;
        case IA::Movement::IA_MOVE_NONE: return {0, 0};break;
        case IA::Movement::IA_MOVE_RIGHT: return {2, 0};break;
        default: return {0, 0}; break;
    }
}

bool AIComponent::putBomb()
{
    return this->_AI->getIAAction() == GameModule::BombermanAction::ACTION_TRIGGER_BOMBE;
}

void AIComponent::setEnv(
    const std::shared_ptr<DataMatrix> &map, std::pair<size_t, size_t> pos, std::vector<std::pair<size_t, size_t>> &enemy)
{
    this->_AI->setIAEnv(AIComponent::translateMatrix(map));
    this->_AI->setEnemyPos(enemy);
    this->_AI->setIAPos(pos);
}

GameModule::MapType AIComponent::translateMatrix(const std::shared_ptr<DataMatrix> &map)
{
    raylib::MyVector2 size = map->getSize();
    std::vector<std::vector<GameModule::TileType>> matrix;
    std::vector<GameModule::TileType> tmp;
    GameModule::TileType Tiletype;

    for (size_t y = 0; y < size.b; y++) {
        tmp.clear();
        for (size_t x = 0; x < size.a; x++) {
            switch (map->getCategory({x, y})) {
                case GUI::BlockFactory::BlockType::BLOCK_BLAST: Tiletype = GameModule::TileType::TILE_EXPLOSION; break;
                case GUI::BlockFactory::BlockType::BLOCK_BOMB: Tiletype = GameModule::TileType::TILE_BOMB; break;
                case GUI::BlockFactory::BlockType::BLOCK_HARD: Tiletype = GameModule::TileType::TILE_HARD; break;
                case GUI::BlockFactory::BlockType::BLOCK_SOFT: Tiletype = GameModule::TileType::TILE_SOFT; break;
                case GUI::BlockFactory::BlockType::BLOCK_FLOOR: Tiletype = GameModule::TileType::TILE_EMPTY; break;
                case GUI::BlockFactory::BlockType::BLOCK_AIR: Tiletype = GameModule::TileType::TILE_EMPTY; break;
                default: Tiletype = GameModule::TileType::TILE_BONUS; break;
            }
            tmp.push_back(Tiletype);
        }
        matrix.push_back(tmp);
    }
    return matrix;
}

raylib::MyVector3 AIComponent::getOrientation() const
{
    return this->_AI->getOrientation();
}

void AIComponent::setRandomness(size_t randomness, bool smoothMode)
{
    size_t value = 100 - randomness;
    this->_AI->setRandomBomb((value) ? value : 1);
    this->_AI->setRandomMove(value);
    this->_smoothMode = smoothMode;
}

bool AIComponent::getMoveType() const
{
    return this->_smoothMode;
}

void AIComponent::setBonusWallPass()
{
    if (!this->_isSet) {
        this->_AI->setRunnableTile(GameModule::TileType::TILE_SOFT);
        this->_isSet = true;
    }
}