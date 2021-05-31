/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Save
*/

#ifndef MODEL_HPP
#define MODEL_HPP

#include "../../include/include.hpp"

#include "IFile.hpp"

namespace raylib
{
    class Save : public IFile
    {
        public :
            Save(const std::string &filepath);
            ~Save();
            void setPath(const std::string &filepath);
            std::shared_ptr<void *> readData(std::size_t &read_size);
            void writeData(std::shared_ptr<void *> data, std::size_t objectSize);

        private :
            std::string _filepath;
            std::shared_ptr<void *> _data;
            std::size_t _readSize;
    };
};

#endif // MODEL_HPP