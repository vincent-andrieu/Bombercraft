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
    try {
        Game::Core core;
        core.loop();
    } catch (const ParserExceptions &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch(...) {
        std::cerr << "Warning: Catch unknown exceptions" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
