/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.hpp - Created: 01/06/2021
 */

#ifndef SAVE_MANAGER_HPP
#define SAVE_MANAGER_HPP

#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <filesystem>
#include <system_error>

typedef std::string string;
typedef std::size_t size_t;
typedef std::stringstream stringstream;
typedef std::fstream fstream;
typedef std::ofstream ofstream;
typedef std::ifstream ifstream;
#define charette_ptr(T) std::shared_ptr<T>
#define toString(str)   std::to_string(str)
#define toInteger(str)  std::stoi(str)
#define toSize_t(str)   std::stoul(str)

namespace Engine
{
    class SaveManager {
      public:
        /**
         * @brief Construct SaveManager starting in a new woking directory
         * @param dirname The name of the directory to be created
         */
        explicit SaveManager(const string &dirname);
        ~SaveManager();

        std::filesystem::path getFileDir(const string &filename);

        /**
         * @brief Create a Directory from the current working directory
         * @param dirname The name of the directory to be created
         */
        void createDirectory(const string &dirname);
        /**
         * @brief Set working directory
         * @param dirname The name of the new working directory
         */
        void setWorkingDirectory(const string &dirname);
        /**
         * @brief Remove the actual working directory from the stack of actual writing directories,
         * so the last working directory is now the actual
         */
        void unsetWorkingDirectory();
        /**
         * @brief Create a file in the current working directory
         * @param filename The name of the file to be created
         */
        void createFile(const string &filename);
        /**
         * @brief Push the file given as parameter on top of the stack of writing files, so when
         * @param filename The name of the file
         */
        void setWritingFile(const string &filename);
        /**
         * @brief Remove the actual writing file from the stack of actual writing files,
         * so the last writing file is now the actual
         */
        void closeWritingFile();
        void closeFile(const string &filename);

        template <typename T> void write(const string &filename, const T &value)
        {
            std::ofstream &file = this->_getFile(filename);

            file.write((char *) &value, sizeof(T));
        }

        template <typename T> void write(const string &filename, const std::vector<T> &value)
        {
            std::ofstream &file = this->_getFile(filename);

            for (const auto &elem : value)
                file.write((char *) &elem, sizeof(T));
        }

        template <typename T, size_t N> void write(const string &filename, const std::array<T, N> &value)
        {
            std::ofstream &file = this->_getFile(filename);

            for (const auto &elem : value)
                file.write((char *) &elem, sizeof(T));
        }

        template <typename Key, typename T> void write(const string &filename, const std::map<Key, T> &value)
        {
            ofstream &file = this->_getFile(filename);

            for (const auto &elem : value) {
                file.write((char *) &elem.first, sizeof(T));
                file.write((char *) &elem.second, sizeof(T));
            }
        }

        template <typename Key, typename T> void write(const string &filename, const std::unordered_map<Key, T> &value)
        {
            ofstream &file = this->_getFile(filename);

            for (const auto &elem : value) {
                file.write((char *) &elem.first, sizeof(Key));
                file.write((char *) &elem.second, sizeof(T));
            }
        }

        template <typename T> void write(const string &filename, const std::unique_ptr<T> &value)
        {
            std::ofstream &file = this->_getFile(filename);

            file.write(value.get(), sizeof(T));
        }

        template <typename T> void write(const string &filename, const std::shared_ptr<T> &value)
        {
            std::ofstream &file = this->_getFile(filename);

            file.write(value.get(), sizeof(T));
        }

        void write(const string &filename, const void *value, std::streamsize size);
        void write(const string &filename, const string &value);

      private:
        [[nodiscard]] std::ofstream &_getFile(const string &filename);

        std::filesystem::path _workingDirectory;
        std::map<std::filesystem::path, std::ofstream> _writingFiles{};
    };
} // namespace Engine

#endif