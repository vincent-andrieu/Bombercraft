/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.hpp - Created: 01/06/2021
 */

#ifndef SAVE_MANAGER_HPP
#define SAVE_MANAGER_HPP

#include <vector>
#include <array>
#include <memory>
#include <fstream>
#include <unordered_map>
#include "GameEngine.hpp"

namespace Engine
{
    class SaveManager {
      public:
        SaveManager() = default;
        ~SaveManager();

        void closeFile(const std::string &filepath);

        template <typename T> void write(const std::string &filepath, const T &value)
        {
            std::ofstream &file = this->_getFile(filepath);

            file.write((char *) &value, sizeof(T));
        }

        template <typename T> void write(const std::string &filepath, const std::vector<T> &value)
        {
            std::ofstream &file = this->_getFile(filepath);

            for (const auto &elem : value)
                file.write((char *) &elem, sizeof(T));
        }

        template <typename T, size_t N> void write(const std::string &filepath, const std::array<T, N> &value)
        {
            std::ofstream &file = this->_getFile(filepath);

            for (const auto &elem : value)
                file.write((char *) &elem, sizeof(T));
        }

        template <typename T> void write(const std::string &filepath, const std::unique_ptr<T> &value)
        {
            std::ofstream &file = this->_getFile(filepath);

            file.write(value.get(), sizeof(T));
        }

        template <typename T> void write(const std::string &filepath, const std::shared_ptr<T> &value)
        {
            std::ofstream &file = this->_getFile(filepath);

            file.write(value.get(), sizeof(T));
        }

        void write(const std::string &filepath, const void *value, std::streamsize size);
        void write(const std::string &filepath, const std::string &value);

      private:
        [[nodiscard]] std::ofstream &_getFile(const std::string &filepath);

        std::unordered_map<std::string, std::ofstream> _files;
    };
} // namespace Engine

#endif