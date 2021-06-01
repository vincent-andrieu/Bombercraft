/*
 * EPITECH PROJECT, 2021
 * SaveManager
 * File description:
 * SaveManager.cpp - Created: 01/06/2021
 */

#include "SaveManager.hpp"

SaveManager::~SaveManager()
{
    for (auto &file : this->_files)
        file.second.close();
}

void SaveManager::closeFile(const string filepath)
{
    this->_files[filepath].close();
    this->_files.erase(filepath);
}

void SaveManager::write(const string filepath, const void *value, size_t size)
{
    ofstream &file = this->_getFile(filepath);

    file.write((const char *) value, size);
}

void SaveManager::write(const string filepath, const string value)
{
    ofstream &file = this->_getFile(filepath);

    file.write(value.c_str(), value.length());
}

ofstream &SaveManager::_getFile(const string &filepath)
{
    if (this->_files.find(filepath) != this->_files.end())
        return this->_files[filepath];

    this->_files[filepath] = ofstream(filepath);
    return this->_files[filepath];
}