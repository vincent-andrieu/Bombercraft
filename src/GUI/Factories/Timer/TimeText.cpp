/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 08/06/2021 TimeText.cpp.cc
*/

#include "TimeText.hpp"

using namespace GUI;

TimeText::TimeText(Engine::Entity owner, const std::string &text, const raylib::MyVector2 position, const std::size_t size,
    const raylib::RColor color, const std::string &fontPath)
    : raylib::Text(text, position, size, color, fontPath), _owner(owner),
      _timerComponent(Game::CoreData::entityManager->getComponent<Engine::Timer>(owner))
{
}

void TimeText::setTime(std::chrono::milliseconds const& time)
{
    std::size_t t = time.count();

    this->_text = std::to_string(t);
}
