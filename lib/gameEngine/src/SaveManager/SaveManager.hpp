/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.hpp - Created: 01/06/2021
 */

#ifndef SAVE_MANAGER_HPP
#define SAVE_MANAGER_HPP

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <filesystem>
#include <system_error>

typedef std::string string;
typedef std::size_t size_t;
typedef std::streamsize streamsize;
typedef std::ofstream ofstream;
typedef std::ifstream ifstream;

namespace Engine
{
    class SaveManager {
      public:
        /**
         * @brief Construct SaveManager starting in a new working directory
         * @param dirname The name of the directory to be created
         */
        explicit SaveManager(const string &dirname = "Engine_Save");
        ~SaveManager();

        std::filesystem::path getFileDir(const string &filename);

        static bool directoryExists(const std::filesystem::path &dirname);
        /**
         * @brief Check if directory Exists in working directory
         * @param dirname The name of the directory to check
         * @return True if directory exists, false otherwise
         */
        bool directoryExistsInWD(const string &dirname);

        static bool fileExists(const std::filesystem::path &dirname);
        bool fileExistsInWD(const string &dirname);

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
         * @brief Get the actual working directory
         * @details In order to place independent files (such as screenshots, infos...)
         * // TODO save screenshot (preview), name and date of save
         * @return A path to the actual working directory
         */
        [[nodiscard]] const std::filesystem::path &getWorkingDirectory() const; // TODO implement

        /**
         * @brief List files and directories in working directory
         * @return A container with the name and the type of each entry in the working directory
         */
        [[nodiscard]] std::filesystem::directory_iterator listWD();

        /**
         * @brief Remove directory contained in working directory
         */
        void removeDirInWD(const std::string &dirname);

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
         * @brief Push the file given as parameter on top of the stack of writing files, so when writeActFile is called, it uses
         * this file
         * @param filename The name of the file
         */
        void setWritingFile(const string &filename);

        /**
         * @brief Remove the actual writing file from the stack of actual writing files,
         * so the last writing file is now the actual
         */
        void closeWritingFile();
        void closeWritingFile(const string &filename);
        /**
         * @brief Push the file given as parameter on top of the stack of reading files, so when readActFile is called, it uses
         * this file
         * @param filename The name of the file
         */
        void setReadingFile(const string &filename);
        /**
         * @brief Remove the actual writing file from the stack of actual writing files,
         * so the last writing file is now the actual
         */
        void closeReadingFile();
        void closeReadingFile(const string &filename);

        template <typename T> void writeActFile(const T value)
        {
            write(_writingFiles.begin()->first.string(), value);
        }
        template <typename T, typename E> void writeActFile(const E data)
        {
            write<T>(_writingFiles.begin()->first, data);
        }

        template <typename T, typename N> void writeActFile(const T value, const N size)
        {
            write(_writingFiles.begin()->first.string(), value, size);
        }
        template <typename T> void readActFile(T &value)
        {
            read(_readingFiles.begin()->first.string(), value);
        }
        template <typename T, typename E> void readActFile(E &data)
        {
            read<T>(_readingFiles.begin()->first, data);
        }
        template <typename T, typename N> void readActFile(T value, const N size)
        {
            read(_readingFiles.begin()->first.string(), value, size);
        }

        static void printException(const std::filesystem::filesystem_error &except);

      private:
        std::filesystem::path _workingDirectory;
        std::map<std::filesystem::path, std::shared_ptr<ofstream>> _writingFiles{};
        std::map<std::filesystem::path, std::shared_ptr<ifstream>> _readingFiles{};

        [[nodiscard]] ofstream &_getWritingFile(const string &filename);
        [[nodiscard]] ifstream &_getReadingFile(const string &filename);

        template <typename T> void write(const string &filename, const T &value)
        {
            ofstream &file = this->_getWritingFile(filename);

            file.write((char *) &value, sizeof(T));
        }

        template <typename T> void write(const string &filename, const std::vector<T> &value)
        {
            ofstream &file = this->_getWritingFile(filename);
            size_t size = value.size();

            file.write((char *) &size, sizeof(size_t));
            for (size_t i = 0; i < size; i++)
                file.write((char *) &value[i], sizeof(T));
        }

        template <typename T, size_t N> void write(const string &filename, const std::array<T, N> &value)
        {
            ofstream &file = this->_getWritingFile(filename);

            for (const auto &elem : value)
                file.write((char *) &elem, sizeof(T));
        }

        template <typename T> void write(const string &filename, const std::unique_ptr<T> &value)
        {
            write(filename, *value);
        }

        template <typename T> void write(const string &filename, const std::shared_ptr<T> &value)
        {
            write(filename, *value);
        }

        void write(const string &filename, const void *value, std::streamsize size);
        void write(const string &filename, const string &value);

        template <typename Key, typename T> void write(const string &filename, const std::map<Key, T> &value)
        {
            ofstream &file = this->_getWritingFile(filename);
            size_t size = value.size();

            file.write((char *) &size, sizeof(size_t));
            for (const auto &elem : value) {
                file.write((char *) &elem.first, sizeof(Key));
                file.write((char *) &elem.second, sizeof(T));
            }
        }

        template <typename Key, typename T> void write(const string &filename, const std::unordered_map<Key, T> &value)
        {
            ofstream &file = this->_getWritingFile(filename);
            size_t size = value.size();

            file.write((char *) &size, sizeof(size_t));
            for (const auto &elem : value) {
                file.write((char *) &elem.first, sizeof(Key));
                file.write((char *) &elem.second, sizeof(T));
            }
        }

        template <typename T> void write(const string &filename, const std::vector<std::vector<T>> &value)
        {
            ofstream &file = this->_getWritingFile(filename);
            size_t sizeY = value.size();
            size_t sizeX = (sizeY > 0) ? value[0].size() : 0;

            file.write((char *) &sizeY, sizeof(size_t));
            file.write((char *) &sizeX, sizeof(size_t));
            for (size_t y = 0; y < sizeY; y++) {
                for (size_t x = 0; x < sizeX; x++) {
                    file.write((char *) &value[y][x], sizeof(T));
                }
            }
        }

        template <typename T> void read(const string &filename, T &value)
        {
            ifstream &file = this->_getReadingFile(filename);

            file.read((char *) &value, sizeof(T));
        }

        /**
         * @brief This method need an empty constructor of T
         *
         * @tparam T
         * @param filename
         * @param value
         */
        template <typename T> void read(const string &filename, std::vector<T> &value)
        {
            value.clear();
            ifstream &file = this->_getReadingFile(filename);
            size_t size = 0;
            T elem;

            file.read((char *) &size, sizeof(size_t));
            for (size_t i = 0; i < size; i++) {
                file.read((char *) &elem, sizeof(T));
                value.push_back(elem);
            }
        }

        template <typename T>
        void read(const string &filename, std::vector<std::vector<T>> &value)
        {
            value.clear();
            ifstream &file = this->_getReadingFile(filename);
            size_t sizeY = 0;
            size_t sizeX = 0;
            T elem;

            file.read((char *) &sizeY, sizeof(size_t));
            file.read((char *) &sizeX, sizeof(size_t));
            if (sizeX > 1000 || sizeY > 1000) {
                std::cerr << "Warning: SaveManager::read too big matrix, abort." << std::endl;
                return; // too big, abort. Maybe corrupted
            }
            for (size_t y = 0; y < sizeY; y++) {
                value.push_back({});
                for (size_t x = 0; x < sizeX; x++) {
                    file.read((char *) &elem, sizeof(T));
                    value[y].push_back(elem);
                }
            }
        }

        template <typename T, size_t N> void read(const string &filename, std::array<T, N> &value)
        {
            ifstream &file = this->_getReadingFile(filename);

            for (auto &elem : value)
                file.read((char *) &elem, sizeof(T));
        }

        /**
         * @brief This method need an empty constructor of T. And a copy constructor of T.
         *
         * @tparam T
         * @param filename
         * @param value
         */
        template <typename T> void read(const string &filename, std::unique_ptr<T> &value)
        {
            ifstream &file = this->_getReadingFile(filename);
            T elem;

            file.read(&elem, sizeof(T));
            value.reset();
            value = std::make_unique<T>(elem);
        }

        /**
         * @brief This method need an empty constructor of T. And a copy constructor of T.
         *
         * @tparam T
         * @param filename
         * @param value
         */
        template <typename T> void read(const string &filename, std::shared_ptr<T> &value)
        {
            ifstream &file = this->_getReadingFile(filename);
            T elem;

            file.read(&elem, sizeof(T));
            value.reset();
            value = std::make_shared<T>(elem);
        }

        template <typename Key, typename T> void read(const string &filename, std::map<Key, T> &value)
        {
            value.clear();
            ifstream &file = this->_getReadingFile(filename);
            size_t size = 0;
            Key key;
            T elem;

            file.read((char *) &size, sizeof(size_t));
            for (size_t i = 0; i < size; i++) {
                file.read((char *) &key, sizeof(Key));
                file.read((char *) &elem, sizeof(T));
                value[key] = elem;
            }
        }

        template <typename Key, typename T> void read(const string &filename, std::unordered_map<Key, T> &value)
        {
            value.clear();
            ifstream &file = this->_getReadingFile(filename);
            size_t size = 0;
            Key key;
            T elem;

            file.read((char *) &size, sizeof(size_t));
            for (size_t i = 0; i < size; i++) {
                file.read((char *) &key, sizeof(Key));
                file.read((char *) &elem, sizeof(T));
                value[key] = elem;
            }
        }

        void read(const string &filename, void *value);
        void read(const string &filename, string &value);
    };
} // namespace Engine

#endif