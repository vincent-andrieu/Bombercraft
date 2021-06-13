/*
 * EPITECH PROJECT, 2021
 * Hitbox
 * File description:
 * Hitbox.cpp - Created: 03/06/2021
 */

#include "Hitbox.hpp"

using namespace Component;

Hitbox::Hitbox(const raylib::MyVector3 &origin, const raylib::MyVector3 &size, hitboxHandler handler)
    : objectBox(std::make_shared<ObjectBox>(origin, size)), _handler(handler)
{
}

void Hitbox::trigger(const Engine::Entity &fromEntity, const Engine::Entity &toEntity)
{
    this->_handler(fromEntity, toEntity);
}

// bool Hitbox::save(Engine::SaveManager &saver) const
// {
//     if (!Component::save(saver))
//         return false;
//     try {
//         saver.createFile(COMP_SAVE_FILE);
//         saver.setWritingFile(COMP_SAVE_FILE);
//         saver.writeActFile(objectBox);
//         saver.writeActFile(_handler);
//         saver.closeWritingFile();
//     } catch (const std::filesystem::filesystem_error &my_e) {
//         Engine::SaveManager::printException(my_e);
//         return false;
//     }
//     return true;
// }
// bool Hitbox::load(Engine::SaveManager &saver)
// {
//     if (!Component::load(saver))
//         return false;
//     try {
//         saver.createFile(COMP_SAVE_FILE);
//         saver.setReadingFile(COMP_SAVE_FILE);
//         saver.readActFile(objectBox);
//         saver.readActFile(_handler);
//         saver.closeReadingFile();
//     } catch (const std::filesystem::filesystem_error &my_e) {
//         Engine::SaveManager::printException(my_e);
//         return false;
//     }
//     return true;
// }