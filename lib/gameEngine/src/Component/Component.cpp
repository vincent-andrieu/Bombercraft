/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 28/05/2021 Component.cpp.c
*/

#include "Component.hpp"

std::size_t Engine::generateComponentType()
{
    static std::size_t counter = 0;

    return counter++;
}