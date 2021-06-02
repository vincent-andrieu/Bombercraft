/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IFile
*/

#ifndef IFILE_HPP
#define IFILE_HPP

#include "../../include/include.hpp"

namespace raylib
{
    class IFile {
      public:
        virtual ~IFile(){};
        virtual void setPath(const string &path) = 0;
        virtual std::shared_ptr<void *> readData(size_t &read_size) = 0;
        virtual void writeData(std::shared_ptr<void *> data, size_t objectSize) = 0;
    };
}; // namespace raylib

#endif // IFILE_HPP