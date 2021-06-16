/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main function
*/

#include <memory>
#include <iostream>
#include "Game/Core/Core.hpp"

std::unique_ptr<Game::Core> core;

static int running_end(const std::string &str)
{
    core.reset();
    std::cerr << str << std::endl;
    return EXIT_ERROR;
}

int main(void)
{
    try {
        core = std::make_unique<Game::Core>();
        core->loop();
    } catch (const ParserExceptions &e) {
        running_end("Fatal error : " + std::string(e.what()));
        return EXIT_ERROR;
    } catch (std::invalid_argument const &e) {
        running_end("Invalid argument : " + std::string(e.what()));
        return EXIT_ERROR;
    } catch (std::filesystem::filesystem_error const &e) {
        running_end("Filesystem : " + std::string(e.what()));
        return EXIT_ERROR;
    } catch (std::exception const &e) {
        running_end(e.what());
        return EXIT_ERROR;
    } catch (...) {
        running_end("Warning: Caught unknown exceptions");
        return EXIT_ERROR;
    }
    core.reset();
    return EXIT_SUCCESS;
}