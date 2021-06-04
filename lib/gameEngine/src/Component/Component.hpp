/*
** EPITECH PROJECT, 2021
** gameEngine
** File description:
** 27/05/2021 Component.hpp.h
*/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <cctype>
#include "SaveManager/SaveManager.hpp"

#define COMP_SAVE_FILE "Component_" + std::to_string(type)

namespace Engine
{
    template <typename T> class Component {
      public:
        Component() = default;
        ~Component() = default;

        /**
         * type : index of the bit (bitset) that identify the component in the Signature (entity.hpp)
         */
        static const std::size_t type;

        virtual void save(SaveManager &saver) const
        {
            try {
                saver.createFile(COMP_SAVE_FILE);
                saver.setWritingFile(COMP_SAVE_FILE);
                saver.writeActFile(type);
                saver.closeWritingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
        }

        virtual void load(SaveManager &saver)
        {
            std::size_t tmp_type = 0;

            try {
                saver.setReadingFile(COMP_SAVE_FILE);
                saver.writeActFile(tmp_type);
                saver.closeReadingFile();
            } catch (const std::filesystem::filesystem_error &my_e) {
                SaveManager::printException(my_e);
            }
            //            if (tmp_type != type) {}
            // TODO do no retreive this data, it is not a good file
            // TODO maybe an assertion or something
        }
    };

    std::size_t generateComponentType();

    template <typename T> const std::size_t Component<T>::type = Engine::generateComponentType();
} // namespace Engine

#endif // COMPONENT_HPP