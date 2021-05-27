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
    class IFile
    {
        public :
            virtual ~IFile() {};

            virtual void setPath(const std::string &path) = 0;

            virtual std::string getData() = 0;

            virtual void updateData(std::string data) = 0;
    };
};

#endif // IFILE_HPP