/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.cpp - Created: 01/06/2021
 */

#include "SaveManager.hpp"

using namespace Engine;

SaveManager::~SaveManager()
{
    for (auto &file : this->_files)
        file.second.close();
}

void SaveManager::closeFile(const std::string &filepath)
{
    this->_files[filepath].close();
    this->_files.erase(filepath);
}

void SaveManager::write(const std::string &filepath, const void *value, std::streamsize size)
{
    ofstream &file = this->_getFile(filepath);

    file.write((const char *) value, size);
}

void SaveManager::write(const std::string &filepath, const std::string &value)
{
    ofstream &file = this->_getFile(filepath);

    file.write(value.c_str(), value.length());
}

ofstream &SaveManager::_getFile(const std::string &filepath)
{
    if (this->_files.find(filepath) != this->_files.end())
        return this->_files[filepath];

    this->_files[filepath] = ofstream(filepath);
    return this->_files[filepath];
}