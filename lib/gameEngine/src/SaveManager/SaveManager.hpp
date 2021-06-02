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
#include <map>
#include <unordered_map>
#include "GameEngine.hpp"

using namespace Engine;

namespace Engine
{
    class SaveManager {
      public:
        SaveManager() = default;
        ~SaveManager();

        void closeFile(const string filepath);

        template <typename T> void write(const string filepath, const T &value)
        {
            ofstream &file = this->_getFile(filepath);

            file.write((char *) &value, sizeof(T));
        }

        template <typename T> void write(const string filepath, const std::vector<T> &value)
        {
            ofstream &file = this->_getFile(filepath);

            for (const auto &elem : value)
                file.write((char *) &elem, sizeof(T));
        }

        template <typename T, size_t N> void write(const string filepath, const std::array<T, N> &value)
        {
            ofstream &file = this->_getFile(filepath);

            for (const auto &elem : value)
                file.write((char *) &elem, sizeof(T));
        }

        template <typename Key, typename T> void write(const string filepath, const std::map<Key, T> &value)
        {
            ofstream &file = this->_getFile(filepath);

            for (const auto &elem : value) {
                file.write((char *) &elem.first, sizeof(T));
                file.write((char *) &elem.second, sizeof(T));
            }
        }

        template <typename Key, typename T> void write(const string filepath, const std::unordered_map<Key, T> &value)
        {
            ofstream &file = this->_getFile(filepath);

            for (const auto &elem : value) {
                file.write((char *) &elem.first, sizeof(Key));
                file.write((char *) &elem.second, sizeof(T));
            }
        }

        template <typename T> void write(const string filepath, const std::unique_ptr<T> &value)
        {
            ofstream &file = this->_getFile(filepath);

            file.write(value.get(), sizeof(T));
        }

        template <typename T> void write(const string filepath, const std::shared_ptr<T> &value)
        {
            ofstream &file = this->_getFile(filepath);

            file.write(value.get(), sizeof(T));
        }

        void write(const string filepath, const void *value, size_t size);
        void write(const string filepath, const string value);

      private:
        [[nodiscard]] ofstream &_getFile(const string &filepath);

        std::unordered_map<string, ofstream> _files;
    };
} // namespace Engine

#endif