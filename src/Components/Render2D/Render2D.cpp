/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.cpp.cc
*/

#include "Render2D.hpp"

#include <utility>

using namespace Component;

Render2D::Render2D(std::shared_ptr<raylib::IRenderable> object) : modele(std::move(object))
{
}

void Render2D::save(Engine::SaveManager &saver) const
{
    try {
        saver.closeWritingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
    }
}
void Render2D::load(Engine::SaveManager &saver)
{
    try {
        saver.closeReadingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
    }
}