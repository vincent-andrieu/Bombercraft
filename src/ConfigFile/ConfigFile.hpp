/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** ConfigFile
*/

#ifndef CONFIGFILE_HPP_
#define CONFIGFILE_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

class ConfigFile {
    public:
        ConfigFile();
        ~ConfigFile();

        void ConfigFile::loadFile(const std::string &filename);

    protected:
    private:
        std::vector<std::string> _fileContent;
};

#endif /* !CONFIGFILE_HPP_ */
