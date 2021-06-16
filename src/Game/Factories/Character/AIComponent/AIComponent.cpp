/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** AIComponent.cpp
*/

#include "AIComponent.hpp"

using namespace Component;

AIComponent::AIComponent() : _AI(std::make_shared<GameModule::IABomberman>())
{
}