/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.cpp - Created: 01/06/2021
 */

#include "SaveManager.hpp"

using namespace Engine;

SaveManager::SaveManager(const string &dirname) : _workingDirectory(std::filesystem::canonical(dirname))
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

inline void SaveManager::createDirectory(const string &dirname)
{
    std::filesystem::path my_path(getFileDir(dirname));

    std::filesystem::create_directory(my_path);
}

void SaveManager::setWorkingDirectory(const string &dirname)
{
    _workingDirectory /= dirname;
    _workingDirectory = std::filesystem::canonical(_workingDirectory);

    if (!std::filesystem::exists(_workingDirectory) || !std::filesystem::is_directory(_workingDirectory)) {
        unsetWorkingDirectory();
        throw std::filesystem::filesystem_error("No such directory", std::make_error_code(std::errc(ENOENT)));
    }
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

    if (!std::filesystem::exists(my_tmp_path) || !std::filesystem::is_regular_file(my_tmp_path))
        throw std::filesystem::filesystem_error("No such file", std::make_error_code(std::errc(ENOENT)));
    _writingFiles.insert(std::make_pair(my_tmp_path, ofstream(my_tmp_path)));
    if (!_writingFiles.at(my_tmp_path).is_open()) {
        _writingFiles.erase(my_tmp_path);
        throw std::filesystem::filesystem_error("File not accessible", std::make_error_code(std::errc(EACCES)));
    }
}

void SaveManager::closeWritingFile()
{
    ofstream &my_stream(_writingFiles.begin()->second);

    if (my_stream.is_open()) {
        my_stream.close();
    }
    _writingFiles.erase(_writingFiles.begin());
}

inline std::filesystem::path SaveManager::getFileDir(const string &filename)
{
    std::filesystem::path my_path(_workingDirectory);

    my_path /= filename;
    return my_path;
}

void SaveManager::closeFile(const string &filename)
{
    std::filesystem::path my_path(getFileDir(filename));

    this->_writingFiles[filename].close();
    this->_writingFiles.erase(filename);
}

void SaveManager::write(const string &filename, const void *value, streamsize size)
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
        return this->_writingFiles[filename];

    this->_writingFiles[filename] = ofstream(filename);
    return this->_writingFiles[filename];
}

ifstream &SaveManager::_getReadingFile(const string &filename)
{
    if (this->_readingFiles.find(filename) != this->_readingFiles.end())
        return this->_readingFiles[filename];

    this->_readingFiles[filename] = ifstream(filename);
    return this->_readingFiles[filename];
}