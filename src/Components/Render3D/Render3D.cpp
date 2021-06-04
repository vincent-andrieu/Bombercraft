/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2DSystem.cpp.cc
*/

#include "Render3D.hpp"

using namespace Component;

Render3D::Render3D(std::shared_ptr<raylib::IRenderable> object) : modele(object)
{
}

bool Render3D::save(Engine::SaveManager &saver) const
{
    if (!Component::save(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setWritingFile(COMP_SAVE_FILE);
        //        saver.writeActFile(modele); // TODO add overload function
        saver.closeWritingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}
bool Render3D::load(Engine::SaveManager &saver)
{
    if (!Component::load(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setReadingFile(COMP_SAVE_FILE);
        //        saver.readActFile(modele); // TODO add overload function
        saver.closeReadingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}