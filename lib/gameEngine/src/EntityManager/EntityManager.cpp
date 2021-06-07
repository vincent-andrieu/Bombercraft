/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 01/06/2021 EntityManager.cpp.c
*/

#include "EntityManager.hpp"

using namespace Engine;

EntityManager::EntityManager(SystemManager &sysManager) : _systemManager(sysManager)
{
    //    load("last_save");
}

EntityManager::~EntityManager()
{
    save("last_save");
}

void EntityManager::allocate(std::size_t size)
{
    for (std::size_t i = 0; i < MAX_COMPONENT; i++) {
        if (_componentRegisters[i]) {
            _componentRegisters[i]->allocate(size);
        }
    }
    _entities.allocate(size);
}

Entity EntityManager::createEntity()
{
    return _entities.create();
}

void EntityManager::removeEntity(Entity entity)
{
    // Hey Entity Register, remove "entity" from your register
    _entities.remove(entity);
    // Hey systems! Remove "entity" from your managed entity lists
    this->_systemManager.onEntityRemoved(entity);
    // Hey Component Registers! Remove the instances of the components of "entity".
    for (auto &componentRegister : _componentRegisters) {
        if (componentRegister != nullptr) {
            componentRegister->tryRemove(entity);
        }
    }
}

SystemManager &EntityManager::getSystemManager()
{
    return _systemManager;
}

void EntityManager::save(const std::string &saveName)
{
    try {
        _saver.createDirectory(saveName);
        _saver.setWorkingDirectory(saveName);
        _entities.save(_saver);
    } catch (const std::filesystem::filesystem_error &my_e) {
        SaveManager::printException(my_e);
        return;
    }
    for (const auto &component_register : _componentRegisters) {
        try {
            if (component_register)
                component_register->save(_saver);
        } catch (const std::filesystem::filesystem_error &my_e) {
            SaveManager::printException(my_e);
            return;
        }
    }
}

void EntityManager::load(const std::string &saveName)
{
    try {
        _saver.setWorkingDirectory(saveName);
        _entities.load(_saver);
    } catch (const std::filesystem::filesystem_error &my_e) {
        SaveManager::printException(my_e);
        return;
    }
    for (const auto &component_register : _componentRegisters) {
        try {
            component_register->load(_saver);
        } catch (const std::filesystem::filesystem_error &my_e) {
            SaveManager::printException(my_e);
        }
    }
}