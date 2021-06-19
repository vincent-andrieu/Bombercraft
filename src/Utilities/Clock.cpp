/*
** EPITECH PROJECT, 2021
** Clock.cpp
** File description:
** add description
*/

#include "Clock.hpp"

void Clock::resetStartingPoint()
{
    _startingPoint = std::chrono::system_clock::now();
}

void Clock::setElapsedTime()
{
    _elapsedTime = std::chrono::system_clock::now() - _startingPoint;
}

[[nodiscard]] const std::chrono::duration<double> &Clock::getElapsedTime() const
{
    return _elapsedTime;
}

[[nodiscard]] double Clock::getElapsedTimeDouble() const
{
    return _elapsedTime.count();
}