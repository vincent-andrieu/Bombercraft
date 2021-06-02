/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** IFile
*/

#ifndef IFILE_HPP
#define IFILE_HPP

#include "../../include/object.hpp"

namespace raylib
{
    class IFile
    {
        public :
            virtual ~IFile() {};
            virtual void setPath(const std::string &path) = 0;
            virtual std::shared_ptr<void *> readData(std::size_t &read_size) = 0;
            virtual void writeData(std::shared_ptr<void *> data, std::size_t objectSize) = 0;
    };
};

#endif // IFILE_HPP