/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <memory>
#include <iostream>
#include "Game/Core/Core.hpp"

int main(void)
{
    Game::Core core;

    core.loop();
    return EXIT_SUCCESS;
}