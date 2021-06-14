/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 EntityRegister.cpp.cc
*/

#include "EntityRegister.hpp"

using namespace Engine;

void EntityRegister::allocate(std::size_t size)
{
    _freeEntities.resize(size);
    std::iota(std::begin(_freeEntities), std::end(_freeEntities), 0);
    _entitySignatures.resize(size);
}

std::vector<Signature> &EntityRegister::getEntitySignatures()
{
    return _entitySignatures;
}

const Signature &EntityRegister::getSignature(Entity entity) const
{
    return _entitySignatures[entity];
}

Entity EntityRegister::create()
{
    Entity entity = 0;

    if (_freeEntities.empty()) {
        entity = static_cast<Entity>(_entitySignatures.size());
        _entitySignatures.emplace_back();
    } else {
        entity = _freeEntities.back();
        _freeEntities.pop_back();
        _entitySignatures[entity].reset();
    }
    return entity;
}

void EntityRegister::remove(Entity entity)
{
    _freeEntities.push_back(entity);
}

// // void EntityRegister::save(SaveManager &saver) const
// // {
// //     saveFreeEntities(saver);
// // }

// void EntityRegister::load(SaveManager &saver)
// {
//     loadFreeEntities(saver);
// }

// void EntityRegister::saveFreeEntities(SaveManager &saver) const
// {
//     const std::string filename("FreeEntities");

//     try {
//         saver.createFile(filename);
//         saver.setWritingFile(filename);
//         saver.writeActFile(_freeEntities);
//         saver.closeWritingFile();
//     } catch (const std::filesystem::filesystem_error &my_e) {
//         SaveManager::printException(my_e);
//     }
// }

// void EntityRegister::loadFreeEntities(SaveManager &saver)
// {
//     const std::string filename("FreeEntities");

//     _freeEntities.clear();
//     try {
//         saver.setWritingFile(filename);
//         saver.readActFile(_freeEntities);
//         saver.closeWritingFile();
//     } catch (const std::filesystem::filesystem_error &my_e) {
//         SaveManager::printException(my_e);
//     }
// }