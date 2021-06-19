/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.cpp - Created: 01/06/2021
 */

#include "SaveManager.hpp"
using namespace Engine;

SaveManager::SaveManager(const std::string &dirname)
{
    try {
        if (!std::filesystem::exists(dirname) || !std::filesystem::is_directory(dirname)) {
            createDirectory(dirname);
        }
        _workingDirectory = std::filesystem::canonical(dirname);
    } catch (const std::filesystem::filesystem_error &my_e) {
        SaveManager::printException(my_e);
    }
}

SaveManager::~SaveManager()
{
    for (auto &file : this->_writingFiles)
        file.second->close();
    for (auto &file : this->_readingFiles)
        file.second->close();
}

// TO REVIEW: https://en.cppreference.com/w/cpp/filesystem/exists
//  first arg of exists and is directory: const std::filesystem::path& p
// inline bool SaveManager::directoryExists(const string &dirname)
inline bool SaveManager::directoryExists(const std::filesystem::path &dirname)
{
    if (std::filesystem::exists(dirname) && std::filesystem::is_directory(dirname)) {
        return true;
    }
    return false;
}

bool SaveManager::directoryExistsInWD(const std::filesystem::path &dirname)
{
    auto my_dirname(getFileDir(dirname));

    return directoryExists(my_dirname);
}

// TO REVIEW: SAME PROBLEME
// inline bool SaveManager::fileExists(const string &dirname)
inline bool SaveManager::fileExists(const std::filesystem::path &dirname)
{
    if (std::filesystem::exists(dirname) && std::filesystem::is_regular_file(dirname)) {
        return true;
    }
    return false;
}

bool SaveManager::fileExistsInWD(const std::filesystem::path &filename)
{
    auto my_filename(getFileDir(filename));
    return fileExists(my_filename);
}

inline void SaveManager::createDirectory(const string &dirname)
{
    std::filesystem::path my_path(getFileDir(dirname));

    std::filesystem::create_directory(my_path);
}

void SaveManager::setWorkingDirectory(const string &dirname)
{
    _workingDirectory /= dirname;
    try {
        _workingDirectory = std::filesystem::canonical(_workingDirectory);
    } catch (const std::filesystem::filesystem_error &my_e) {
        SaveManager::printException(my_e);
        unsetWorkingDirectory();
    }

    if (!directoryExists(_workingDirectory)) {
        unsetWorkingDirectory();
        throw std::filesystem::filesystem_error(
            "Cannot use directory", _workingDirectory, std::make_error_code(std::errc(ENOENT)));
    }
}

const std::filesystem::path &SaveManager::getWorkingDirectory() const
{
    return _workingDirectory;
}

inline void SaveManager::unsetWorkingDirectory()
{
    _workingDirectory.replace_filename("");
}

void SaveManager::createFile(const string &filename)
{
    std::filesystem::path my_tmp_path(getFileDir(filename));
    ofstream my_stream;

    my_stream.open(my_tmp_path);
    if (!my_stream.is_open())
        throw std::filesystem::filesystem_error("File not accessible", std::make_error_code(std::errc(EACCES)));
    // TODO add magic number and header
    my_stream.close();
}

void SaveManager::setWritingFile(const string &filename)
{
    std::filesystem::path my_tmp_path(getFileDir(filename));

    if (!fileExists(my_tmp_path))
        throw std::filesystem::filesystem_error(filename, std::make_error_code(std::errc(ENOENT)));
    _writingFiles.insert(std::make_pair(my_tmp_path, std::make_unique<ofstream>(my_tmp_path)));
    if (!_writingFiles.at(my_tmp_path)->is_open()) {
        _writingFiles.erase(my_tmp_path);
        throw std::filesystem::filesystem_error(filename, std::make_error_code(std::errc(EACCES)));
    }
}

void SaveManager::closeWritingFile()
{
    this->_writingFiles.begin()->second->close();
    this->_writingFiles.erase(_writingFiles.begin());
}

void SaveManager::closeWritingFile(const string &filename)
{
    this->_writingFiles[filename]->close();
    this->_writingFiles.erase(filename);
}

void SaveManager::setReadingFile(const string &filename)
{
    std::filesystem::path my_tmp_path(getFileDir(filename));

    if (!fileExists(my_tmp_path))
        throw std::filesystem::filesystem_error(filename, std::make_error_code(std::errc(ENOENT)));
    _readingFiles.insert(std::make_pair(my_tmp_path, std::make_unique<ifstream>(my_tmp_path)));
    if (!_readingFiles.at(my_tmp_path)->is_open()) {
        _readingFiles.erase(my_tmp_path);
        throw std::filesystem::filesystem_error(filename, std::make_error_code(std::errc(EACCES)));
    }
    // TODO add magic number and header
}

void SaveManager::closeReadingFile()
{
    this->_readingFiles.begin()->second->close();
    this->_readingFiles.erase(_readingFiles.begin());
}

void SaveManager::closeReadingFile(const string &filename)
{
    this->_readingFiles[filename]->close();
    this->_readingFiles.erase(filename);
}

inline std::filesystem::path SaveManager::getFileDir(const string &filename)
{
    std::filesystem::path my_path(_workingDirectory);

    my_path /= filename;
    return my_path;
}

void SaveManager::write(const string &filename, const void *value, std::streamsize size)
{
    ofstream &file = this->_getWritingFile(filename);

    file.write((char *) &size, sizeof(size_t));
    file.write((const char *) value, size);
}

void SaveManager::write(const string &filename, const string &value)
{
    ofstream &file = this->_getWritingFile(filename);
    size_t size = value.length() + 1;

    file.write((char *) &size, sizeof(size_t));
    file.write(value.c_str(), size);
}

void SaveManager::read(const string &filename, void *value)
{
    ifstream &file = this->_getReadingFile(filename);
    size_t size;

    file.read((char *) &size, sizeof(size_t));
    file.read((char *) value, size);
}

void SaveManager::read(const string &filename, string &value)
{
    ifstream &file = this->_getReadingFile(filename);
    size_t size;
    char *dest;

    file.read((char *) &size, sizeof(size_t));
    dest = new char[size];
    file.read(dest, size);
    value = dest;
    delete dest;
}

ofstream &SaveManager::_getWritingFile(const string &filename)
{
    if (this->_writingFiles.find(filename) != this->_writingFiles.end())
        return *this->_writingFiles[filename];

    this->_writingFiles[filename] = std::make_unique<ofstream>(filename);
    return *this->_writingFiles[filename];
}

ifstream &SaveManager::_getReadingFile(const string &filename)
{
    if (this->_readingFiles.find(filename) != this->_readingFiles.end())
        return *this->_readingFiles[filename];

    this->_readingFiles[filename] = std::make_unique<ifstream>(filename);
    return *this->_readingFiles[filename];
}

void SaveManager::printException(const std::filesystem::filesystem_error &except)
{
    std::cerr << except.what() << std::endl;
}