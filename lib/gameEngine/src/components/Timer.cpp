/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 Timer.cpp.c
*/

#include "Timer.hpp"

using namespace Engine;

Timer::Timer(double seconds, EntityManager &entityManager, SceneManager &sceneManager, scriptHandler handler)
    : interval(seconds), startTime(NOW), script(entityManager, sceneManager, handler)
{
}

void Timer::start()
{
    this->startTime = NOW;
}

bool Timer::eval(Entity entity)
{
    double delta = (NOW - this->startTime);

    if (delta >= interval) {
        this->start();
        script.trigger(entity);
        return true;
    }
    return false;
}

[[nodiscard]] double Timer::getDelta() const
{
    return (NOW - this->startTime);
}

bool Timer::save(SaveManager &saver) const
{
    if (!Component::save(saver))
        return false;
    try {
        saver.createFile(COMP_SAVE_FILE);
        saver.setWritingFile(COMP_SAVE_FILE);
        saver.writeActFile(interval);
        saver.writeActFile(startTime);
        //                saver.writeActFile(script); // TODO handle script ?
        saver.closeWritingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        SaveManager::printException(my_e);
        return false;
    }
    return true;
}

bool Timer::load(SaveManager &saver)
{
    if (!Component::load(saver))
        return false;
    try {
        saver.setReadingFile(COMP_SAVE_FILE);
        saver.readActFile(interval);
        saver.readActFile(startTime);
        //                saver.writeActFile(script); // TODO handle script ?
        saver.closeReadingFile();
    } catch (const std::filesystem::filesystem_error &my_e) {
        SaveManager::printException(my_e);
        return false;
    }
    return true;
}