/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Save
*/

#include <cstring>
#include "Save.hpp"

raylib::Save::Save(const std::string &filepath) : _filepath(filepath), _data(nullptr), _readSize(0)
{
    unsigned int read_size = 0;
    void *filedata = nullptr;

    if (FileExists(this->_filepath.c_str())) {
        filedata = LoadFileData(this->_filepath.c_str(), &read_size);
        this->_data = std::make_shared<void *>(filedata);
        this->_readSize = read_size;
    }
}

raylib::Save::~Save()
{
    this->_filepath.clear();
    if (this->_data)
        UnloadFileData((unsigned char *) this->_data.get());
}

void raylib::Save::setPath(const std::string &filepath)
{
    unsigned int read_size = 0;
    void *filedata = nullptr;

    if (this->_data)
        UnloadFileData((unsigned char *) this->_data.get());
    this->_data = nullptr;
    this->_readSize = 0;
    this->_filepath = filepath;
    if (FileExists(this->_filepath.c_str())) {
        filedata = LoadFileData(this->_filepath.c_str(), &read_size);
        this->_data = std::make_shared<void *>(filedata);
        this->_readSize = read_size;
    }
}

std::shared_ptr<void *> raylib::Save::readData(std::size_t &read_size)
{
    if (this->_data && this->_readSize) {
        read_size = this->_readSize;
        return this->_data;
    } else {
        throw std::invalid_argument("No data load");
    }
}

void raylib::Save::writeData(std::shared_ptr<void *> data, std::size_t objectSize)
{
    if (FileExists(this->_filepath.c_str())) {
        if (!objectSize)
            throw std::invalid_argument("SIZE 0: Impossible to write");
        if (!data.get())
            throw std::invalid_argument("NULLPTR: Impossible to write");
        if (!SaveFileData(this->_filepath.c_str(), data.get(), objectSize))
            throw std::invalid_argument("Failed write: Impossible to write");
    } else {
        throw std::invalid_argument("Invalide filepath: Impossible to write");
    }
}