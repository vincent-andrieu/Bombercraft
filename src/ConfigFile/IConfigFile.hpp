/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** IConfigFile
*/

#ifndef ICONFIGFILE_HPP
#define ICONFIGFILE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

#include "../../lib/raylibCpp/src/Data/MyVector/MyVector2.hpp"
#include "../../lib/raylibCpp/src/Data/MyVector/MyVector3.hpp"
#include "../../lib/raylibCpp/src/Data/MyVector/MyVector4.hpp"

class IConfigFile {
    public:
        virtual ~IConfigFile() {};
        virtual void loadFile(const std::string &filename) = 0;

        virtual int getInt(const std::string name) const = 0;
        virtual float getFloat(const std::string name) const = 0;
        virtual std::string getString(const std::string name) const = 0;
        virtual std::pair<int, int> getPaire(const std::string name) const = 0;

        virtual raylib::MyVector2 getMyVector2(const std::string name) const = 0;
        virtual raylib::MyVector3 getMyVector3(const std::string name) const = 0;
        virtual raylib::MyVector4 getMyVector4(const std::string name) const = 0;

        virtual std::vector<int> getTabInt(const std::string name) const = 0;
        virtual std::vector<std::vector<int>> getTabTabInt(const std::string name) const = 0;
        /*
        ** OTHER
        **
        **  virtual TYPE getType(const std::string name) const = 0;
        **
        */
};

#endif
