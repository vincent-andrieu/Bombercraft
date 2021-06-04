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

// template <typename T> void Engine::Component<T>::save(SaveManager &saver) const
//{
//     const std::string filename("Entity_" + std::to_string(type));
//
//     saver.createFile(filename);
//     saver.setWritingFile(filename);
//     saver.writeActFile(type);
// }

// template <typename T> void Engine::Component<T>::load(SaveManager &saver)
//{
//     const std::string filename("Entity_" + std::to_string(type));
//
//     saver.setWritingFile(filename);
//     saver.writeActFile(type);
// }