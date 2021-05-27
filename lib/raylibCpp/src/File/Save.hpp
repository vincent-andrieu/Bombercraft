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
            Save(const std::string &path);
            ~Save();

            void setPath(const std::string &path);

            std::string getData();

            void updateData(std::string data);

        private :
            std::string _path;
            std::string _data;
    };
};

#endif // MODEL_HPP