/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** ConfigFile
*/

#include "ConfigFile.hpp"

ConfigFile::ConfigFile()
{
}

ConfigFile::~ConfigFile()
{
}

void ConfigFile::loadFile(const std::string &filename)
{
    std::string line;
    std::ifstream myfile (filename);
    std::regex isAscii ("^[\\x00-\\x7F]+$");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (!std::regex_search(line, isAscii) && !line.empty()) {
                throw ParserExceptions("The file doesn't contains only ASCII characters !");
            } else {
                _fileContent.push_back(line);
            }
        }
    } else {
        throw std::invalid_argument("File close");
    }
}