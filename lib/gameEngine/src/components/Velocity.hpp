/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 Velocity.hpp.h
*/

#ifndef VELOCITY_HPP
#define VELOCITY_HPP

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

        void save(SaveManager &saver) const override
        {
            try {
                saver.closeWritingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }
        void load(SaveManager &saver) override
        {
            try {
                saver.closeReadingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }
    };
} // namespace Engine

#endif // VELOCITY_HPP