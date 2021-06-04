/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 Position.hpp.h
*/

#ifndef POSITION_HPP
#define POSITION_HPP

#include "Component/Component.hpp"

namespace Engine
{
    struct Position : public Component<Position> {
        Position(float x, float y) : x(x), y(y)
        {
        }
        Position() : x(0), y(0)
        {
        }

        float x;
        float y;

        void save(SaveManager &saver) const override
        {
            try {
                saver.createFile(COMP_SAVE_FILE);
                saver.setWritingFile(COMP_SAVE_FILE);
                saver.writeActFile(x);
                saver.writeActFile(y);
                saver.closeWritingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }
        void load(SaveManager &saver) override
        {
            try {
                saver.setReadingFile(COMP_SAVE_FILE);
                saver.readActFile(x);
                saver.readActFile(y);
                saver.closeReadingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }
    };
} // namespace Engine

#endif // POSITION_HPP