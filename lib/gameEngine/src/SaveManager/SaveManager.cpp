/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.cpp - Created: 01/06/2021
 */

#include "SaveManager.hpp"

using namespace Engine;

SaveManager::SaveManager(const std::string &dirname) : _workingDirectory(std::filesystem::canonical(dirname))
{
    if (!std::filesystem::exists(_workingDirectory) || !std::filesystem::is_directory(_workingDirectory)) {
        createDirectory(_workingDirectory);
    }
}

SaveManager::~SaveManager()
{
    for (auto &file : this->_writingFiles)
        file.second.close();
}

inline bool SaveManager::directoryExists(const std::string &dirname)
{
    if (std::filesystem::exists(dirname) && std::filesystem::is_directory(dirname)) {
        return true;
    }
    return false;
}

inline bool SaveManager::fileExists(const std::string &dirname)
{
    if (std::filesystem::exists(dirname) && std::filesystem::is_regular_file(dirname)) {
        return true;
    }
    return false;
}

inline void SaveManager::createDirectory(const std::string &dirname)
{
    std::filesystem::path my_path(getFileDir(dirname));

    std::filesystem::create_directory(my_path);
}

void SaveManager::setWorkingDirectory(const std::string &dirname)
{
    _workingDirectory /= dirname;
    _workingDirectory = std::filesystem::canonical(_workingDirectory);

    if (!directoryExists(_workingDirectory)) {
        unsetWorkingDirectory();
        throw std::filesystem::filesystem_error("No such directory", std::make_error_code(std::errc(ENOENT)));
    }
}

inline void SaveManager::unsetWorkingDirectory()
{
    _workingDirectory.replace_filename("");
}

void SaveManager::createFile(const std::string &filename)
{
    std::filesystem::path my_tmp_path(getFileDir(filename));
    std::ofstream my_stream;

    my_stream.open(my_tmp_path);
    if (!my_stream.is_open())
        throw std::filesystem::filesystem_error("File not accessible", std::make_error_code(std::errc(EACCES)));
    // TODO add magic number and header
    my_stream.close();
}

void SaveManager::setWritingFile(const std::string &filename)
{
    std::filesystem::path my_tmp_path(getFileDir(filename));

    if (!fileExists(my_tmp_path))
        throw std::filesystem::filesystem_error("No such file", std::make_error_code(std::errc(ENOENT)));
    _writingFiles.insert(std::make_pair(my_tmp_path, std::ofstream(my_tmp_path)));
    if (!_writingFiles.at(my_tmp_path).is_open()) {
        _writingFiles.erase(my_tmp_path);
        throw std::filesystem::filesystem_error("File not accessible", std::make_error_code(std::errc(EACCES)));
    }
}

void SaveManager::closeWritingFile()
{
    std::ofstream &my_stream(_writingFiles.begin()->second);

    if (my_stream.is_open()) {
        my_stream.close();
    }
    _writingFiles.erase(_writingFiles.begin());
}

inline std::filesystem::path SaveManager::getFileDir(const std::string &filename)
{
    std::filesystem::path my_path(_workingDirectory);

    my_path /= filename;
    return my_path;
}

void SaveManager::closeFile(const std::string &filename)
{
    std::filesystem::path my_path(getFileDir(filename));

    this->_writingFiles[filename].close();
    this->_writingFiles.erase(filename);
}

void SaveManager::write(const std::string &filename, const void *value, std::streamsize size)
{
    std::ofstream &file = this->_getFile(filename);

    file.write((const char *) value, size);
}

void SaveManager::write(const std::string &filename, const std::string &value)
{
    std::ofstream &file = this->_getFile(filename);

    file.write(value.c_str(), value.length());
}

std::ofstream &SaveManager::_getFile(const std::string &filename)
{
    if (this->_writingFiles.find(filename) != this->_writingFiles.end())
        return this->_writingFiles[filename];

    this->_writingFiles[filename] = std::ofstream(filename);
    return this->_writingFiles[filename];
}