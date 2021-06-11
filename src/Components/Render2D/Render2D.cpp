/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 02/06/2021 Render2D.cpp.cc
*/

#include "Render2D.hpp"

using namespace Component;

Render2D::Render2D(render2dMapModels const &models) : ARender2D(models)
{
}

void Render2D::draw()
{
    for (auto &model : _models) {
        model->draw();
    }
}

bool Render2D::save(Engine::SaveManager &saver) const
{
    if (!Component::save(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setWritingFile(COMP_SAVE_FILE);
        //        saver.writeActFile(model); // TODO add overload function
        saver.closeWritingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}
bool Render2D::load(Engine::SaveManager &saver)
{
    if (!Component::load(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setReadingFile(COMP_SAVE_FILE);
        //        saver.readActFile(model); // TODO add overload function
        saver.closeReadingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}