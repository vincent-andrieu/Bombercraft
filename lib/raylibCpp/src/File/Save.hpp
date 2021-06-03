/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Save
*/

#ifndef SAVE_HPP
#define SAVE_HPP

#include "../../include/object.hpp"

#include "IFile.hpp"

#include "export.hpp"

namespace raylib
{
    class EXPORT Save : public IFile {
      public:
        Save(const string &filepath);
        ~Save();
        void setPath(const string &filepath);
        std::shared_ptr<void *> readData(size_t &read_size);
        void writeData(std::shared_ptr<void *> data, size_t objectSize);

      private:
        string _filepath;
        std::shared_ptr<void *> _data;
        size_t _readSize;
    };
}; // namespace raylib

#endif // SAVE_HPP