/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 09/06/2021 Timer.cpp.c
*/

#include "Timer.hpp"

using namespace Engine;

Timer::Timer(double seconds, EntityManager &entityManager, SceneManager &sceneManager, scriptHandler handler)
    : interval(seconds), startTime(NOW), script(entityManager, sceneManager, handler), _inPause(false), _savedDuration(0)
{
}

void Timer::start()
{
    this->startTime = NOW;
}

bool Timer::eval(Entity entity)
{
    if (!_inPause) {
        double delta = (NOW - this->startTime);

        if (delta >= interval) {
            this->start();
            script.trigger(entity);
            return true;
        }
    }
    return false;
}

double Timer::getDelta() const
{
    return (NOW - this->startTime);
}

void Timer::pause()
{
    if (!this->_inPause) {
        this->_inPause = true;
        this->_savedDuration = this->getDelta();
    }
}

void Timer::resume()
{
    if (this->_inPause) {
        this->_inPause = false;
        this->startTime = (NOW - _savedDuration);
    }
}

bool Timer::isPaused() const
{
    return _inPause;
}
