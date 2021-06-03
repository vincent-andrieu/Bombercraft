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

class IConfigFile {
    public:
        virtual ~IConfigFile() {};
        virtual void loadFile(const std::string &filename) = 0;
        virtual int getInt(const std::string name) const = 0;
        virtual float getFloat(const std::string name) const = 0;
        virtual std::string getString(const std::string name) const = 0;
        virtual std::pair<int, int> getPaire(const std::string name) const = 0;
        /*
        ** OTHER
        **
        **  virtual TYPE getType(const std::string name) const = 0;
        **
        */
};

#endif
