/*
** EPITECH PROJECT, 2021
** SingleRender2D.cpp
** File description:
** Implementation of class allowing to handle several render elements, but render a single
*/

#include "SingleRender2D.hpp"

Component::SingleRender2D::SingleRender2D(const render2dMapModels &models) : ARender2D(models)
{
}

void Component::SingleRender2D::draw()
{
    std::cout << "in" << std::endl;
    _models.at(_actRender2D)->draw();
    std::cout << "out" << std::endl;
}

void Component::SingleRender2D::setActRender2D(const string &label)
{
    try {
        _actRender2D = _modelIndex.at(label);
    } catch (const std::out_of_range &my_e) {
        std::cerr << "Can't access " << label << std::endl;
    }
}

bool Component::SingleRender2D::save(Engine::SaveManager &saver) const
{
    if (!Component::save(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setWritingFile(COMP_SAVE_FILE);
        //        saver.writeActFile(model); // TODO add overload function
        //        saver.writeActFile(_actRender2D); // TODO add overload function
        saver.closeWritingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}
bool Component::SingleRender2D::load(Engine::SaveManager &saver)
{
    if (!Component::load(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setReadingFile(COMP_SAVE_FILE);
        //        saver.readActFile(model); // TODO add overload function
        //        saver.readActFile(_actRender2D); // TODO add overload function
        saver.closeReadingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        Engine::SaveManager::printException(my_e);
        return false;
    }
    return true;
}