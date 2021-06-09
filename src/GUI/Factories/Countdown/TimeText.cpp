/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 TimeText.cpp.cc
*/

#include "TimeText.hpp"
#include <sstream>
#include <iomanip>

using namespace GUI;

TimeText::TimeText(Engine::Entity owner, const std::string &text, const raylib::MyVector2 position, const std::size_t size,
    const raylib::RColor color, const std::string &fontPath)
    : raylib::Text(text, position, size, color, fontPath),
      _timerComponent(Game::CoreData::entityManager->getComponent<Engine::Timer>(owner))
{
}

void TimeText::setTime(double const& time)
{
    const std::size_t totalSeconds = static_cast<std::size_t>(time);
    const std::size_t minutes = (totalSeconds / 60);
    const std::size_t secondes = (totalSeconds % 60);
    std::stringstream ss;

    ss << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << secondes;
    this->_text = ss.str();
}
