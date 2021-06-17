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
        return running_end("Fatal error : " + std::string(e.what()));
    } catch (std::invalid_argument const &e) {
        return running_end("Invalid argument : " + std::string(e.what()));
    } catch (std::filesystem::filesystem_error const &e) {
        return running_end("Filesystem : " + std::string(e.what()));
    } catch (std::exception const &e) {
        return running_end(e.what());
    } catch (...) {
        return running_end("Warning: Caught unknown exceptions");
    }
    core.reset();
    return EXIT_SUCCESS;
}