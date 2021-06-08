/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 Velocity.hpp.h
*/

#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include "Component/Component.hpp"

namespace Engine
{
    struct Velocity : public Component<Velocity> {
        Velocity(float x, float y) : x(x), y(y)
        {
        }
        Velocity() : x(0), y(0)
        {
        }

        float x;
        float y;

        bool save(SaveManager &saver) const override
        {
            if (!Component::save(saver))
                return false;
            try {
                saver.createFile(COMP_SAVE_FILE);
                saver.setWritingFile(COMP_SAVE_FILE);
                saver.writeActFile(x);
                saver.writeActFile(y);
                saver.closeWritingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
                return false;
            }
            return true;
        }
        bool load(SaveManager &saver) override
        {
            if (!Component::load(saver))
                return false;
            try {
                saver.setReadingFile(COMP_SAVE_FILE);
                saver.readActFile(x);
                saver.readActFile(y);
                saver.closeReadingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
                return false;
            }
            return true;
        }
    };
} // namespace Engine

#endif // VELOCITY_HPP