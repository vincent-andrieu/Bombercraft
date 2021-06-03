/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <memory>
#include <iostream>
#include "Game/Core/Core.hpp"
#include "Unistd.hpp"

int main(void)
{
    Game::Core core;
    std::cout << Cross::Unistd::my_access(std::string("CMakeLists.txt"), Cross::aMode::fOk) << std::endl;
    core.loop();
    return EXIT_SUCCESS;
}