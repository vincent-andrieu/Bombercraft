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

void Render3D::save(Engine::SaveManager &saver) const
{
    try {
        saver.closeWritingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
    }
}

void Render3D::load(Engine::SaveManager &saver)
{
    try {
        saver.closeReadingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
    }
}